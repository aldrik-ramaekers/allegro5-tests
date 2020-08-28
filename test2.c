
#include "allegro5/allegro.h"
#include <stdio.h>

const float FPS = 60;

int main(int argc, char* argv[])
{
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	
	bool running = true;
	bool redraw = true;
	
	// Initialize allegro
	if (!al_init()) {
		printf("Failed to initialize allegro.\n");
		return 1;
	}
	
	if (!al_install_keyboard()) {
	}
	
	
	// Initialize the timer
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		printf("Failed to create timer.\n");
		return 1;
	}
	
	// Create the display
	//al_set_new_display_refresh_rate(120);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(640, 480);
	if (!display) {
		printf("Failed to create display.\n");
		return 1;
	}
	
	event_queue = al_create_event_queue();
	if (!event_queue) {
		printf("Failed to create event queue.\n");
	}
	
	
	printf("refresh rate:%d", al_get_display_refresh_rate(display));
	
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	ALLEGRO_EVENT event;
	while(1)
	{
		al_wait_for_event(event_queue, &event);
		
		switch (event.type) {
			case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				return 0;
			}
			break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
			return 0;
		}
	}
	
}