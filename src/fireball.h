#ifndef __FIREBALL__
#define __FIREBALL__

#include <stdlib.h>
#include <stdio.h>
#include "rect.h"

#define FIREBALL_STEPS 15
#define FIREBALL_SIDE 15

enum FireballDirections {
        FIREBALL_LEFT,
        FIREBALL_RIGHT,
        FIREBALL_UP,
        FIREBALL_DOWN
};

enum FireballFlags {
        FIREBALL_FUNC_SUCCESS,
        FIREBALL_INIT_ERROR,
        FIREBALL_DESTROY_ERROR,
        FIREBALL_INVALID_ERROR
};

typedef struct Fireball {
        unsigned short side;
        unsigned short init_x;
        unsigned short init_y;
        unsigned char left;
        unsigned char right;
        unsigned char up;
        unsigned char down;
        unsigned char damage;
} Fireball;

/* Cria um disparo */
Fireball *init_fireball(unsigned short side, unsigned short init_x, unsigned short init_y, unsigned short max_x, unsigned short max_y);

/* Calcula colisão entre retângulo e disparo. Retorna 1 se houver colisão entre 'rect' e 'fireball' */
unsigned char collision_rect_fireball(Rectangle *rect, Fireball *fireball);

/* Indica a direção do disparo. Retorna 1 se colidir com um retângulo ou com a borda da janela */
unsigned char mv_fireball(Fireball *fireball, Rectangle *rect1, Rectangle *rect2, unsigned short max_x, unsigned short max_y);

/* Destrói o disparo */
unsigned char destroy_fireball(Fireball *fireball);

#endif // __FIREBALL__