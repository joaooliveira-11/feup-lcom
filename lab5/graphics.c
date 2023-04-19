#include "graphics.h"

vbe_mode_info_t vbe_mode_info;
uint8_t* frame_buffer;


int (changeTo_graphic_mode)(uint16_t submode){
    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));
    reg86.ax = 0x4F02;
    reg86.bx = submode | BIT(14);
    reg86.intno = 0x10;
    if(sys_int86(&reg86) != 0){
        printf("Error while trying to change to graphics mode\n");
        return 1;
    }
    return 0;
}    

// Igual à vg_exit()
int (changeTo_text_mode)(){
    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));
    reg86.ax = 0x0003;
    reg86.bx = 0x0000;
    reg86.intno = 0x10;
    if(sys_int86(&reg86) != 0){
        printf("Error while trying to change to text mode\n");
        return 1;
    }
    return 0;
}

int (frame_buffer_build)(uint16_t mode){

    memset(&vbe_mode_info, 0, sizeof(vbe_mode_info));
    if(vbe_get_mode_info(mode, &vbe_mode_info) != 0) return 1;

    unsigned int bytesPerPixel = (vbe_mode_info.BitsPerPixel + 7) / 8;  //converter o número de bits por pixel em bytes
    unsigned int frame_buffer_size = vbe_mode_info.XResolution * vbe_mode_info.YResolution * bytesPerPixel;  // tamanho da memoria da VRAM
    
    struct minix_mem_range frameBuffer_physic_address;
    frameBuffer_physic_address.mr_base = vbe_mode_info.PhysBasePtr;   // endereço físico base do frame buffer
    frameBuffer_physic_address.mr_limit = frameBuffer_physic_address.mr_base + frame_buffer_size; // endereço físico final do frame buffer

    if(sys_privctl(SELF, SYS_PRIV_ADD_MEM, &frameBuffer_physic_address)) {
        printf("Error while allocating physical memory for frame buffer\n");
        return 1;
    }

    frame_buffer = vm_map_phys(SELF, (void*) frameBuffer_physic_address.mr_base, frame_buffer_size);
    if (frame_buffer == NULL) {
        printf("Error while allocating virtual memory for frame buffer\n");
        return 1;
    }

    return 0;
}

int (color_pixel)(uint16_t x, uint16_t y, uint32_t color){

    if(x > vbe_mode_info.XResolution || x < 0 ||  y > vbe_mode_info.YResolution || y < 0) return 1;
    unsigned int bytesPerPixel = (vbe_mode_info.BitsPerPixel + 7) / 8;

    unsigned int frame_buffer_index = (vbe_mode_info.XResolution * y + x) * bytesPerPixel; // zona do frame buffer onde começa o pixel (x, y)

    if(memcpy(&frame_buffer[frame_buffer_index], &color, bytesPerPixel) == NULL) return 1;  // copiar bytesPerPixel bytes da color na zona do frame buffer onde começa o pixel (x, y)

    return 0;   
}

// função auxiliar para desenhar o rectangle
int (draw_horizontal_line)(uint16_t x, uint16_t y, uint16_t length, uint32_t color) {
  for(unsigned i = 0 ; i < length ; i++){ 
    if(color_pixel(x+i, y, color) != 0) return 1;
  }
  return 0;
}

int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for(uint16_t i = 0; i < height ; i++){
    if(draw_horizontal_line(x, y+i, width, color) != 0) {
      vg_exit(); // se der erro voltar a colocar em text mode
      return 1;
    }
  }
  return 0;
}

int (fix_colorMode_bits)(uint32_t color, uint32_t *color_fix){
  if (vbe_mode_info.BitsPerPixel == 32) {
    *color_fix = color;
  } else {
    *color_fix = color & (BIT(vbe_mode_info.BitsPerPixel) - 1);
  }
  return 0;
}

uint32_t(direct_color)(uint32_t red_, uint32_t green_, uint32_t blue_) {
  return (green_ << vbe_mode_info.GreenFieldPosition) | (blue_ << vbe_mode_info.BlueFieldPosition) | (red_ << vbe_mode_info.RedFieldPosition);
}

uint32_t(indexed_color)(uint16_t col, uint16_t row, uint8_t step, uint32_t first, uint8_t no_rectangles) {
  return (first + (row * no_rectangles + col) * step) % (1 << vbe_mode_info.BitsPerPixel);
}

uint32_t(R_first)(uint32_t first) {
  return (first >> vbe_mode_info.RedFieldPosition) & ((1 << vbe_mode_info.RedMaskSize) - 1);
}

uint32_t(G_first)(uint32_t first) {
  return (first >> vbe_mode_info.GreenFieldPosition) & ((1 << vbe_mode_info.GreenMaskSize) - 1);
}

uint32_t(B_first)(uint32_t first) {
  return (first >> vbe_mode_info.BlueFieldPosition) & ((1 << vbe_mode_info.RedMaskSize) - 1);
}

uint32_t(R)(unsigned col, uint8_t step, uint32_t first) {
  return (R_first(first) + col * step) % (1 << vbe_mode_info.RedMaskSize);
}

uint32_t(G)(unsigned row, uint8_t step, uint32_t first) {
  return (G_first(first) + row * step) % (1 << vbe_mode_info.RedMaskSize);
}

uint32_t(B)(unsigned row, unsigned col, uint8_t step, uint32_t first) {
  return (B_first(first) + (col + row) * step) % (1 << vbe_mode_info.RedMaskSize);
}

int(video_pattern)(uint8_t no_rectangles, uint32_t first, uint8_t step){
  int height = vbe_mode_info.YResolution / no_rectangles;
  int width = vbe_mode_info.XResolution / no_rectangles;

  for(int h = 0; h < no_rectangles; h++){
    for(int w = 0; w < no_rectangles; w++){
      uint32_t color;

      if(vbe_mode_info.MemoryModel == DIRECT_COLOR){
        color = direct_color(R(w,step,first), G(h,step,first), B(w,h,step,first));
      }
      else{
        color = indexed_color(w,h,step,first,no_rectangles);
      }
      
      if(draw_rectangle(w * width, h * height, width, height, color) != 0) return 1;
    }
  }
  return 0;
}

int (print_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {

  xpm_image_t img;

  uint8_t *colors_array = xpm_load(xpm, XPM_INDEXED, &img);

  for (int h = 0 ; h < img.height ; h++) {
    for (int w = 0 ; w < img.width ; w++) {
      if (color_pixel(x + w, y + h, *colors_array) != 0) return 1;
      colors_array++;
    }
  }
  return 0;
}
