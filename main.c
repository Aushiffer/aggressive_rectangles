#include "joystick.h"
#include "rect.h"

#define WINDOW_H 480
#define WINDOW_W 640

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

        Rectangle *rect1 = init_rectangle(30, 50, 25, WINDOW_H / 2, WINDOW_W, WINDOW_H);
        Rectangle *rect2 = init_rectangle(30, 50, WINDOW_W - 25, WINDOW_H / 2, WINDOW_W, WINDOW_H);

        if (!rect1 || !rect2) {
                fprintf(stderr, "[-] main(): ocorreu a invalidez de algum dos retangulos\n");
                exit(RECT_INVALID_ERROR);
        }

        while (1) {
                al_wait_for_event(ev_queue, &ev);

                if (ev.type == ALLEGRO_EVENT_TIMER) {
                        update_pos(rect1, rect2, WINDOW_W, WINDOW_H);
                        al_clear_to_color(al_map_rgb(255, 255, 255));
                        al_draw_filled_rectangle(rect1->init_x - (float)rect1->width / 2, rect1->init_y - (float)rect1->height / 2, rect1->init_x + (float)rect1->width / 2, rect1->init_y + (float)rect1->height / 2, al_map_rgb(0, 0, 0));
                        al_draw_filled_rectangle(rect2->init_x - (float)rect2->width / 2, rect2->init_y - (float)rect2->height / 2, rect2->init_x + (float)rect2->width / 2, rect2->init_y + (float)rect2->height / 2, al_map_rgb(0, 255, 0));
                        al_flip_display();
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
                } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                        break;
                }
        }

        destroy_rectangle(rect1);
        destroy_rectangle(rect2);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(ev_queue);

        return FUNCTION_SUCCESS;
}
