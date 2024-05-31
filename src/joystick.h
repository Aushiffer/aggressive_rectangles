#ifndef __JOYSTICK__
#define __JOYSTICK__

#include <stdlib.h>

typedef struct Joystick {
        unsigned char up;
        unsigned char down;
        unsigned char left;
        unsigned char right;
} Joystick;

/* Cria um joystick para movimentação */
Joystick *init_joystick();

/* Move para baixo */
void mv_joystick_down(Joystick *joystick);

/* Move para cima */
void mv_joystick_up(Joystick *joystick);

/* Move para a esquerda */
void mv_joystick_left(Joystick *joystick);

/* Move para a direita */
void mv_joystick_right(Joystick *joystick);

/* Destrói o joystick */
void destroy_joystick(Joystick *joystick);

#endif // __JOYSTICK__