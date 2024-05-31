#include "joystick.h"

Joystick *init_joystick() {
        Joystick *joystick = (Joystick *)malloc(sizeof(Joystick));

        if (!joystick)
                return NULL;

        joystick->down = 0;
        joystick->up = 0;
        joystick->left = 0;
        joystick->right = 0;

        return joystick;
}

void mv_joystick_down(Joystick *joystick) {
        joystick->down = joystick->down ^ 1;
}

void mv_joystick_up(Joystick *joystick) {
        joystick->up = joystick->up ^ 1;
}

void mv_joystick_left(Joystick *joystick) {
        joystick->left = joystick->left ^ 1;
}

void mv_joystick_right(Joystick *joystick) {
        joystick->right = joystick->right ^ 1;
}

void destroy_joystick(Joystick *joystick) {
        free(joystick);
        joystick = NULL;
}