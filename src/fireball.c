#include "fireball.h"
#include <stdio.h>

Fireball *init_fireball(unsigned short side, unsigned short init_x, unsigned short init_y, unsigned short max_x, unsigned short max_y) {
        if ((init_x - side / 2 < 0) || (init_x + side / 2  > max_x) ||(init_y - side / 2 < 0) || (init_y + side / 2 > max_y))
                return NULL;

        Fireball *fireball = (Fireball *)malloc(sizeof(Fireball));

        if (!fireball) {
                fprintf(stderr, "[-] init_fireball(): falha na inicializacao do disparo\n");
                exit(FIREBALL_INIT_ERROR);
        }

        fireball->init_x = init_x;
        fireball->init_y = init_y;
        fireball->side = side;
        fireball->left = 0;
        fireball->right = 0;
        fireball->down = 0;
        fireball->up = 0;

        return fireball;
}

unsigned char collision_rect_fireball(Rectangle *rect, Fireball *fireball) {
        if (!rect || !fireball) {
                fprintf(stderr, "[-] collision_rect_fireball(): algum dos argumentos eh invalido\n");
                exit(FIREBALL_INVALID_ERROR);
        }

        if ((((fireball->init_x + fireball->side / 2 >= rect->init_x - rect->width / 2) && (rect->init_x - rect->width / 2 >= fireball->init_x - fireball->side / 2)) 
        || ((rect->init_x + rect->width / 2 >= fireball->init_x - fireball->side / 2) && (fireball->init_x - fireball->side / 2 >= rect->init_x - rect->width / 2))) 
        && (((fireball->init_y + fireball->side / 2 >= rect->init_y - rect->height / 2) && (rect->init_y - rect->height / 2 >= fireball->init_y - fireball->side / 2)) 
        || ((rect->init_y + rect->height / 2 >= fireball->init_y - fireball->side / 2) && (fireball->init_y - fireball->side / 2 >= rect->init_y - rect->height / 2)))) {
                return 1;
        }

        return 0;
}