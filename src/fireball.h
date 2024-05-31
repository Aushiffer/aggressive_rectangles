#ifndef __FIREBALL__
#define __FIREBALL__

#include <stdlib.h>
#include <stdio.h>
#include "rect.h"

enum FireballDirections {
        FIREBALL_LEFT,
        FIREBALL_RIGHT,
        FIREBALL_UP,
        FIREBALL_DOWN
};

typedef struct Fireball {
        unsigned short side;
        unsigned short init_x;
        unsigned short init_y;
        unsigned char left;
        unsigned char right;
        unsigned char up;
        unsigned char down;
} Fireball;

/* Cria um disparo */
Fireball *init_fireball(unsigned short side, unsigned short init_x, unsigned short init_y, unsigned short max_x, unsigned short max_y);

/* Calcula colisão entre retângulo e disparo */
unsigned char collision_rect_fireball(Rectangle *rect, Fireball *fireball);

/* Indica a direção do disparo */
void mv_fireball(Fireball *fireball, unsigned char direction);

/* Destrói o disparo */
unsigned char destroy_fireball(Fireball *fireball);

#endif // __FIREBALL__