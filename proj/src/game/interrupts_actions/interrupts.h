#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include "../../devices/util/KBC.h"
#include "../../devices/mouse/mouse.h"
#include "../../devices/graphics/graphics.h"
#include "../elements/sprite/sprite.h"
#include "../draw/draw.h"
#include "../elements/elements.h"
#include "../moves/moves.h"
#include "../settings.h"

void handle_timer_interrupt();
void handle_keyboard_interrupt();
void handle_mouse_interrupt();

#endif
