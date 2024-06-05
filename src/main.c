#include "joystick.h"
#include "rect.h"
#include "fireball.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#define WINDOW_W 640
#define WINDOW_H 480

enum PersistFlags {
        PERSIST_LEFT = 1,
        PERSIST_RIGHT,
        PERSIST_UP,
        PERSIST_DOWN
};

int main(void) {
        al_init();
        al_init_primitives_addon();
        al_install_keyboard();

        ALLEGRO_DISPLAY *display = al_create_display(WINDOW_W, WINDOW_H);
        ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
        ALLEGRO_EVENT_QUEUE *ev_queue = al_create_event_queue();
        ALLEGRO_EVENT ev;

        al_register_event_source(ev_queue, al_get_display_event_source(display));
        al_register_event_source(ev_queue, al_get_timer_event_source(timer));
        al_register_event_source(ev_queue, al_get_keyboard_event_source());
        al_start_timer(timer);

        Rectangle *rect1 = init_rectangle(30, 50, 50, WINDOW_H / 2, WINDOW_W, WINDOW_H);
        Rectangle *rect2 = init_rectangle(30, 50, WINDOW_W - 50, WINDOW_H / 2, WINDOW_W, WINDOW_H);
        Fireball *fireball1 = init_fireball(FIREBALL_SIDE, rect1->init_x, rect1->init_y, WINDOW_W, WINDOW_H);
        Fireball *fireball2 = init_fireball(FIREBALL_SIDE, rect2->init_x, rect2->init_y, WINDOW_W, WINDOW_H);
        
        if (!rect1 || !rect2 || !fireball1 || !fireball2) {
                fprintf(stderr, "[-] main(): ocorreu a invalidez de alguma entidade\n");
                exit(RECT_INVALID_ERROR);
        }
        
        unsigned char persist1 = 0; /* valor default */
        unsigned char persist2 = 0; /* valor default */
        unsigned char fire1 = 0; /* valor default */
        unsigned char fire2 = 0; /* valor default */
        unsigned char mv_value1, mv_value2;

        while (1) {
                al_wait_for_event(ev_queue, &ev);

                if (ev.type == ALLEGRO_EVENT_TIMER) {
                        update_pos(rect1, rect2, WINDOW_W, WINDOW_H);
                        al_clear_to_color(al_map_rgb(255, 255, 255));

                        mv_value1 = mv_fireball(fireball1, rect1, rect2, WINDOW_W, WINDOW_H);
                        mv_value2 = mv_fireball(fireball2, rect2, rect1, WINDOW_W, WINDOW_H);

                        if (mv_value1 != 1) {
                                if (fire1) {
                                        al_draw_filled_rectangle(fireball1->init_x - (float)fireball1->side / 2, fireball1->init_y - (float)fireball1->side / 2, fireball1->init_x + (float)fireball1->side / 2, fireball1->init_y + (float)fireball1->side / 2, al_map_rgb(255, 0, 0));
                                } else {
                                        fireball1->init_x = rect1->init_x;
                                        fireball1->init_y = rect1->init_y;

                                        al_draw_filled_rectangle(fireball1->init_x - (float)fireball1->side / 2, fireball1->init_y - (float)fireball1->side / 2, fireball1->init_x + (float)fireball1->side / 2, fireball1->init_y + (float)fireball1->side / 2, al_map_rgb(255, 0, 0));
                                }
                        } else {
                                fireball1->left = 0;
                                fireball1->right = 0;
                                fireball1->up = 0;
                                fireball1->down = 0;
                                fire1 = 0;
                        }

                        if (mv_value2 != 1) {
                                if (fire2) {
                                        al_draw_filled_rectangle(fireball2->init_x - (float)fireball2->side / 2, fireball2->init_y - (float)fireball2->side / 2, fireball2->init_x + (float)fireball2->side / 2, fireball2->init_y + (float)fireball2->side / 2, al_map_rgb(0, 0, 255));
                                } else {
                                        fireball2->init_x = rect2->init_x;
                                        fireball2->init_y = rect2->init_y;

                                        al_draw_filled_rectangle(fireball2->init_x - (float)fireball2->side / 2, fireball2->init_y - (float)fireball2->side / 2, fireball2->init_x + (float)fireball2->side / 2, fireball2->init_y + (float)fireball2->side / 2, al_map_rgb(0, 0, 255));
                                }
                        } else {
                                fireball2->left = 0;
                                fireball2->right = 0;
                                fireball2->up = 0;
                                fireball2->down = 0;
                                fire2 = 0;
                        }

                        al_draw_filled_rectangle(rect1->init_x - (float)rect1->width / 2, rect1->init_y - (float)rect1->height / 2, rect1->init_x + (float)rect1->width / 2, rect1->init_y + (float)rect1->height / 2, al_map_rgb(0, 0, 0));
                        al_draw_filled_rectangle(rect2->init_x - (float)rect2->width / 2, rect2->init_y - (float)rect2->height / 2, rect2->init_x + (float)rect2->width / 2, rect2->init_y + (float)rect2->height / 2, al_map_rgb(0, 255, 0));
                        al_flip_display();

                        if (rect1->init_x < rect2->init_x && rect1->init_y == rect2->init_y) {
                                persist1 = PERSIST_RIGHT;
                                persist2 = PERSIST_LEFT;
                        } else if (rect2->init_x < rect1->init_x && rect1->init_y == rect2->init_y) {
                                persist1 = PERSIST_LEFT;
                                persist2 = PERSIST_RIGHT;
                        } else if (rect1->init_y < rect2->init_y && rect1->init_x == rect2->init_x) {
                                persist1 = PERSIST_DOWN;
                                persist2 = PERSIST_UP;
                        } else if (rect2->init_y < rect1->init_y && rect1->init_x == rect2->init_x) {
                                persist1 = PERSIST_UP;
                                persist2 = PERSIST_DOWN;
                        }
                } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_UP) {
                        switch (ev.keyboard.keycode) {
                                case ALLEGRO_KEY_A:
                                mv_joystick_left(rect1->controller);

                                break;

                                case ALLEGRO_KEY_D:
                                mv_joystick_right(rect1->controller);

                                break;

                                case ALLEGRO_KEY_W:
                                mv_joystick_up(rect1->controller);

                                break;

                                case ALLEGRO_KEY_S:
                                mv_joystick_down(rect1->controller);

                                break;
                        }

                        switch (ev.keyboard.keycode) {
                                case ALLEGRO_KEY_LEFT:
                                mv_joystick_left(rect2->controller);

                                break;

                                case ALLEGRO_KEY_RIGHT:
                                mv_joystick_right(rect2->controller);

                                break;

                                case ALLEGRO_KEY_UP:
                                mv_joystick_up(rect2->controller);

                                break;

                                case ALLEGRO_KEY_DOWN:
                                mv_joystick_down(rect2->controller);

                                break;
                        }
        
                        if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                                fire1 = 1;

                                switch (persist1) {
                                        case PERSIST_LEFT:
                                        fireball1->left += 1;

                                        break;

                                        case PERSIST_RIGHT:
                                        fireball1->right += 1;

                                        break;

                                        case PERSIST_UP:
                                        fireball1->up += 1;

                                        break;

                                        case PERSIST_DOWN:
                                        fireball1->down += 1;

                                        break;

                                        default:
                                        printf("[-] Something went REALLY wrong, so I'm not moving the fireball (P1)\n Persist value: %d\n", persist1);

                                        break;
                                }
                        }

                        if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                                fire2 = 1;

                                switch (persist2) {
                                        case PERSIST_LEFT:
                                        fireball2->left += 1;

                                        break;

                                        case PERSIST_RIGHT:
                                        fireball2->right += 1;

                                        break;

                                        case PERSIST_UP:
                                        fireball2->up += 1;

                                        break;

                                        case PERSIST_DOWN:
                                        fireball2->down += 1;

                                        break;

                                        default:
                                        printf("[-] Something went REALLY wrong, so I'm not moving the fireball (P2)\n Persist value: %d\n", persist1);

                                        break;
                                }
                        }
                } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                        break;
                }
        }

        destroy_fireball(fireball1);
        destroy_fireball(fireball2);
        destroy_rectangle(rect1);
        destroy_rectangle(rect2);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(ev_queue);

        return FUNCTION_SUCCESS;
}
