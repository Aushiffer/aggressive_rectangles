#include "persist.h"

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