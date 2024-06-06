#include "rect.h"

Rectangle *init_rectangle(unsigned short height, unsigned short width, unsigned short init_x, unsigned short init_y, unsigned short max_x, unsigned short max_y) {
        if ((init_x - width / 2 < 0) || (init_x + width / 2 > max_x) || (init_y - height / 2 < 0) || (init_y + height / 2 > max_y)) {
                fprintf(stderr, "[-] init_rectangle(): posicao invalida de retangulo\n");
                exit(RECT_INIT_ERROR);
        }

        Rectangle *rect = (Rectangle *)malloc(sizeof(Rectangle));

        if (!rect) {
                fprintf(stderr, "[-] init_rectangle(): falha na inicializacao do retangulo\n");
                exit(RECT_INIT_ERROR);
        }

        rect->init_x = init_x;
        rect->init_y = init_y;
        rect->height = height;
        rect->width = width;
        rect->health_points = MAX_HEALTH_POINTS;
        rect->controller = init_joystick();

        if (!rect->controller) {
                fprintf(stderr, "[-] init_rectangle(): falha na inicializacao do joystick\n");
                exit(RECT_INIT_ERROR);
        }

        return rect;
}

unsigned char collision_rect(Rectangle *rect1, Rectangle *rect2) {
        if ((((rect1->init_x + rect1->width / 2 >= rect2->init_x - rect2->width / 2) && (rect2->init_x - rect2->width / 2 >= rect1->init_x - rect1->width / 2)) 
        || ((rect2->init_x + rect2->width / 2 >= rect1->init_x - rect1->width / 2) && (rect1->init_x - rect1->width / 2 >= rect2->init_x - rect2->width / 2))) 
        && (((rect1->init_y + rect1->height / 2 >= rect2->init_y - rect2->height / 2) && (rect2->init_y - rect2->height / 2 >= rect1->init_y - rect1->height / 2)) 
        || ((rect2->init_y + rect2->height / 2 >= rect1->init_y - rect1->height / 2) && (rect1->init_y - rect1->height / 2 >= rect2->init_y - rect2->height / 2)))) {
                return 1;
        }

        return 0;
}

void mv_rectangle(Rectangle *rect, char instance_steps, unsigned char traject, unsigned short max_x, unsigned short max_y) {
        if (!rect) {
                fprintf(stderr, "[-] mv_rectangle(): retangulo invalido\n");
                exit(RECT_INVALID_ERROR);
        }
        
        if (traject == LEFT) {
                /* Esquerda */
                if ((rect->init_x - instance_steps * STEPS) - rect->width / 2 >= 0)
                        rect->init_x = rect->init_x - instance_steps * STEPS;
        } else if (traject == RIGHT) {
                /* Direita */
                if ((rect->init_x + instance_steps * STEPS) + rect->width / 2 <= max_x)
                        rect->init_x = rect->init_x + instance_steps * STEPS;
        } else if (traject == UP) {
                /* Cima */
                if ((rect->init_y - instance_steps * STEPS) - rect->height / 2 >= 0)
                        rect->init_y = rect->init_y - instance_steps * STEPS;
        } else if (traject == DOWN) {
                /* Baixo */
                if ((rect->init_y + instance_steps * STEPS) + rect->height / 2 <= max_y)
                        rect->init_y = rect->init_y + instance_steps * STEPS;
        }
}

void update_pos(Rectangle *rect1, Rectangle *rect2, unsigned short max_x, unsigned short max_y) {
        if (!rect1 || !rect2) {
                fprintf(stderr, "[-] update_pos(): retangulo invalido\n");
                exit(RECT_INVALID_ERROR);
        }

        if (rect1->controller->left == 1) {
                mv_rectangle(rect1, 1, LEFT, max_x, max_y);

                if (collision_rect(rect1, rect2))
                        mv_rectangle(rect1, -1, LEFT, max_x, max_y);
        } else if (rect1->controller->right == 1) {
                mv_rectangle(rect1, 1, RIGHT, max_x, max_y);

                if (collision_rect(rect1, rect2))
                        mv_rectangle(rect1, -1, RIGHT, max_x, max_y);
        } else if (rect1->controller->up == 1) {
                mv_rectangle(rect1, 1, UP, max_x, max_y);

                if (collision_rect(rect1, rect2))
                        mv_rectangle(rect1, -1, UP, max_x, max_y);
        } else if (rect1->controller->down == 1) {
                mv_rectangle(rect1, 1, DOWN, max_x, max_y);

                if (collision_rect(rect1, rect2))
                        mv_rectangle(rect1, -1, DOWN, max_x, max_y);
        }

        if (rect2->controller->left == 1) {
                mv_rectangle(rect2, 1, LEFT, max_x, max_y);

                if (collision_rect(rect1, rect2))
                        mv_rectangle(rect2, -1, LEFT, max_x, max_y);
        } else if (rect2->controller->right == 1) {
                mv_rectangle(rect2, 1, RIGHT, max_x, max_y);

                if (collision_rect(rect1, rect2))
                        mv_rectangle(rect2, -1, RIGHT, max_x, max_y);
        } else if (rect2->controller->up == 1) {
                mv_rectangle(rect2, 1, UP, max_x, max_y);

                if (collision_rect(rect1, rect2))
                        mv_rectangle(rect2, -1, UP, max_x, max_y);
        } else if (rect2->controller->down == 1) {
                mv_rectangle(rect2, 1, DOWN, max_x, max_y);

                if (collision_rect(rect1, rect2))
                        mv_rectangle(rect2, -1, DOWN, max_x, max_y);
        }
}

unsigned char is_dead(Rectangle *rect) {
        if (rect->health_points != 0)
                return 0;

        return 1;
}

void update_persist(Rectangle *rect1, Rectangle *rect2, unsigned char *persist1, unsigned char *persist2) {
        if (rect1->init_x < rect2->init_x && rect1->init_y == rect2->init_y) {
                *persist1 = PERSIST_RIGHT;
                *persist2 = PERSIST_LEFT;
        } else if (rect2->init_x < rect1->init_x && rect1->init_y == rect2->init_y) {
                *persist1 = PERSIST_LEFT;
                *persist2 = PERSIST_RIGHT;
        } else if (rect1->init_y < rect2->init_y && rect1->init_x == rect2->init_x) {
                *persist1 = PERSIST_DOWN;
                *persist2 = PERSIST_UP;
        } else if (rect2->init_y < rect1->init_y && rect1->init_x == rect2->init_x) {
                *persist1 = PERSIST_UP;
                *persist2 = PERSIST_DOWN;
        }
}

unsigned char destroy_rectangle(Rectangle *rect) {
        if (rect && rect->controller) {
                destroy_joystick(rect->controller);
                free(rect);

                rect = NULL;

                return FUNCTION_SUCCESS;
        }

        exit(RECT_DESTROY_ERROR);
}