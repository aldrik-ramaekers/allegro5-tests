
#include "allegro5/allegro.h"
#include <stdio.h>

#define WIDTH        640
#define HEIGHT       480

/* globals */
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_DISPLAY     *display;

#define abort_example(text) printf(text); return 0;

int main(int argc, char**argv)
{
	if (!al_init()) {
		abort_example("Could not init Allegro.\n");
	}
	
	display = al_create_display(WIDTH, HEIGHT);
	if (!display) {
		abort_example("al_create_display failed\n");
	}
	al_clear_to_color(al_map_rgb_f(0, 0, 0));
	al_flip_display();
	
	if (!al_install_keyboard()) {
		abort_example("al_install_keyboard failed\n");
	}
	
	event_queue = al_create_event_queue();
	if (!event_queue) {
		abort_example("al_create_event_queue failed\n");
	}
	
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	ALLEGRO_EVENT event;
	while(1)
	{
		al_wait_for_event(event_queue, &event);
		
		switch (event.type) {
			case ALLEGRO_EVENT_KEY_DOWN:
			printf("KEY DOWN: %d\n", event.keyboard.modifiers);
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				return 0;
			}
			break;
			
			case ALLEGRO_EVENT_KEY_UP:
			printf("KEY UP: %d\n", event.keyboard.modifiers);
			break;
			
			case ALLEGRO_EVENT_KEY_CHAR:
			printf("CHAR: %d\n", event.keyboard.modifiers);
			break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
			return 0;
		}
	}
	
	return 0;
}