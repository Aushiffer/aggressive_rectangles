#ifndef __RECT__
#define __RECT__

#define STEPS 10

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <stdio.h>
#include "joystick.h"

enum Directions {
        LEFT,
        RIGHT,
        UP,
        DOWN
};

enum RectFlags {
        FUNCTION_SUCCESS,
        RECT_INIT_ERROR,
        RECT_INVALID_ERROR,
        RECT_DESTROY_ERROR,
        RECT_INVALID_DIRECTION_ERROR
};

typedef struct Rectangle {
        unsigned short height;
        unsigned short width;
        unsigned short init_x;
        unsigned short init_y;
        Joystick *controller;
} Rectangle;

/* Cria um retângulo */
Rectangle *init_rectangle(unsigned short height, unsigned short width, unsigned short init_x, unsigned short init_y, unsigned short max_x, unsigned short max_y);

/* Verifica se ocorreu colisão entre os retângulos */
unsigned char collision(Rectangle *rect1, Rectangle *rect2);

/* Move o retângulo 'instance_steps' passos, em 'traject' direção */
void mv_rectangle(Rectangle *rect, char instance_steps, unsigned char traject, unsigned short max_x, unsigned short max_y);

/* Atualiza as coordenadas do retângulo, verificando colisões */
void update_pos(Rectangle *rect1, Rectangle *rect2, unsigned short max_x, unsigned short max_y);

/* Destrói o retângulo */
unsigned char destroy_rectangle(Rectangle *rect);

#endif // __RECT__