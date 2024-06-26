#ifndef __RECT__
#define __RECT__

#define STEPS 10
#define MAX_HEALTH_POINTS 100

#include <stdlib.h>
#include <stdio.h>
#include "joystick.h"

enum RectDirections {
        LEFT,
        RIGHT,
        UP,
        DOWN
};

enum RectFlags {
        FUNCTION_SUCCESS,
        RECT_INIT_ERROR,
        RECT_INVALID_ERROR,
        RECT_DESTROY_ERROR
};

enum PersistFlags {
        PERSIST_LEFT = 1,
        PERSIST_RIGHT,
        PERSIST_UP,
        PERSIST_DOWN
};

typedef struct Rectangle {
        unsigned short height;
        unsigned short width;
        unsigned short init_x;
        unsigned short init_y;
        unsigned char health_points;
        Joystick *controller;
} Rectangle;

/* Cria um retângulo */
Rectangle *init_rectangle(unsigned short height, unsigned short width, unsigned short init_x, unsigned short init_y, unsigned short max_x, unsigned short max_y);

/* Verifica se ocorreu colisão entre os retângulos */
unsigned char collision_rect(Rectangle *rect1, Rectangle *rect2);

/* Move o retângulo 'instance_steps' passos, em 'traject' direção */
void mv_rectangle(Rectangle *rect, char instance_steps, unsigned char traject, unsigned short max_x, unsigned short max_y);

/* Atualiza as coordenadas do retângulo, verificando colisões */
void update_pos(Rectangle *rect1, Rectangle *rect2, unsigned short max_x, unsigned short max_y);

/* Checa se o retângulo morreu */
unsigned char is_dead(Rectangle *rect);

/* Atualiza as flags de persistência relativas à movimentação do disparo */
void update_persist(Rectangle *rect1, Rectangle *rect2, unsigned char *persist1, unsigned char *persist2);

/* Destrói o retângulo */
unsigned char destroy_rectangle(Rectangle *rect);

#endif // __RECT__