#include "fireball.h"
#include "rect.h"
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
        fireball->damage = 10;

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
                (rect->health_points) -= fireball->damage;

                return 1;
        }

        return 0;
}

unsigned char mv_fireball(Fireball *fireball, Rectangle *rect1, Rectangle *rect2, unsigned short max_x, unsigned short max_y) {
        if (!fireball || !rect1 || !rect2) {
                fprintf(stderr, "[-] mv_fireball(): algum dos argumentos eh invalido\n");
                exit(FIREBALL_INVALID_ERROR);
        }

        if (fireball->left != 0) {
                fireball->init_x = fireball->init_x - FIREBALL_STEPS;

                if (collision_rect_fireball(rect2, fireball) || (fireball->init_x - FIREBALL_STEPS) - fireball->side / 2 < 0)
                        return 1;
        } else if (fireball->right != 0) {
                fireball->init_x = fireball->init_x + FIREBALL_STEPS;

                if (collision_rect_fireball(rect2, fireball) || (fireball->init_x + FIREBALL_STEPS) + fireball->side / 2 > max_x)
                        return 1;
        } else if (fireball->up != 0) {
                fireball->init_y = fireball->init_y - FIREBALL_STEPS;

                if (collision_rect_fireball(rect2, fireball) || (fireball->init_y - FIREBALL_STEPS) - fireball->side / 2 < 0)
                        return 1;
        } else if (fireball->down != 0) {
                fireball->init_y = fireball->init_y + FIREBALL_STEPS;

                if (collision_rect_fireball(rect2, fireball) || (fireball->init_y + FIREBALL_STEPS) + fireball->side / 2 > max_y)
                        return 1;
        }

        return 0;
}

unsigned char destroy_fireball(Fireball *fireball) {
        if (fireball) {
                free(fireball);
                fireball = NULL;

                return FIREBALL_FUNC_SUCCESS;
        }

        fprintf(stderr, "[-] destroy_fireball(): erro no destrutor do disparo\n");
        exit(FIREBALL_DESTROY_ERROR);
}