#include "view.h"

// Variáveis externas importantes à visualização do modelo e dos seus estados
uint8_t *main_frame_buffer;
uint8_t *secondary_frame_buffer;
uint8_t *drawing_frame_buffer;
uint32_t frame_buffer_size;
extern vbe_mode_info_t vbe_mode_info;
extern GameState gamestate;

// Objetos
extern sprite_t *smile;
extern sprite_t *button1;
extern sprite_t *button2;
extern sprite_t *button3;
extern sprite_t *button4;

// Alocação de memória ao(s) buffer(s)
// Se houver só um buffer, esse é o principal
// Se houver double buffering, há um secundário a alocar a mesma quantidade de memória que serve
// exclusivamente para o desenho
int set_frame_buffers(uint16_t mode) {
    if (frame_buffer_build(mode, &main_frame_buffer)) return 1;
    frame_buffer_size = vbe_mode_info.XResolution * vbe_mode_info.YResolution * ((vbe_mode_info.BitsPerPixel + 7) / 8);
    if (ACTIVE_DOUBLE_Buffer) {
        secondary_frame_buffer = (uint8_t *) malloc(frame_buffer_size);
        drawing_frame_buffer = secondary_frame_buffer;
    } else {
        drawing_frame_buffer = main_frame_buffer;
    }
    return 0;
}

// Double buffering
// Cópia para o frame buffer principal do frame construído desde a última atualização
// Otimização: 
// como o swap é uma operação muito frequente, é melhor não estar  a calcular frame_buffer_size sempre. 
// Assim opta-se por uma variável global, que é constante ao longo da execução e calculada 1 vez na linha 30.
// Poupa-se (frequência * (2 multiplicações + 1 soma + 1 divisão)) operações por cada segundo.
void swap_buffers() {
    memcpy(main_frame_buffer, secondary_frame_buffer, frame_buffer_size);
}

// A construção de um novo frame é baseado:
// - no estado atual do modelo (menuState, mouse_info, mode_info, buttonX->pressed...);
// - no Algoritmo do Pintor - https://pt.wikipedia.org/wiki/Algoritmo_do_pintor
// A ideia é colocar no buffer primeiro o plano mais longe do observador (a cor do fundo) e só depois 
// os objetos em cima, no caso do cursor e / ou dos botões
void draw_new_frame() {
    switch (gamestate) {
        case START_MENU:
            draw_initial_menu();
            break;
        case PLAYING:
            draw_game_menu();
            break;
    }
}

// O menu inicial é apenas um retângulo com tamanho máximo, com um smile ao centro
void draw_initial_menu() {
    draw_rectangle(0, 0, vbe_mode_info.XResolution, vbe_mode_info.YResolution, RED, drawing_frame_buffer);
    draw_sprite_xpm(smile, vbe_mode_info.XResolution/2 - 100, vbe_mode_info.YResolution/2 - 100);
}

// O menu do jogo é constituído por quatro botões
void draw_game_menu() {
    draw_sprite_button(button1, 0, 0);
    draw_sprite_button(button2, vbe_mode_info.XResolution/2, 0);
    draw_sprite_button(button3, 0, vbe_mode_info.YResolution/2);
    draw_sprite_button(button4, vbe_mode_info.XResolution/2, vbe_mode_info.YResolution/2);
}

// A função recebe um objeto Sprite proveniente de um XPM e mostra-o nas coordenadas (x, y)
// Usa as cores dinamicamente alocadas na altura da construção
// A função ignora a cor transparente do XPM para não modificar o fundo quando não é preciso
int draw_sprite_xpm(sprite_t *sprite, int x, int y) { 
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t current_color;
    for (int h = 0 ; h < height ; h++) {
      for (int w = 0 ; w < width ; w++) {
        current_color = sprite->colors_array[w + h*width];
        if (current_color == TRANSPARENT) continue;
        if (color_pixel(x + w, y + h, current_color, drawing_frame_buffer) != 0) return 1;
      }
    }
    return 0; 
}

// A função recebe um objeto Sprite de cor constante e mostra-o nas coordenadas (x, y)
// Usa apenas uma cor, alocada na altura da construção
// A função ignora a cor transparente do XPM para não modificar o fundo quando não é preciso
int draw_sprite_button(sprite_t *sprite, int x, int y) { 
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t color = sprite->is_pressed ? PRESSED : sprite->main_color;
    for (int h = 0 ; h < height ; h++) {
      for (int w = 0 ; w < width ; w++) {
        if (color_pixel(x + w, y + h, color, drawing_frame_buffer) != 0) return 1;
      }
    }
    return 0; 
}
