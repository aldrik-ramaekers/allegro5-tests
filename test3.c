/*
 *    Example program for the Allegro library.
 *
 *    Demonstrate 'simple' audio interface.
 */

#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

#define RESERVED_SAMPLES   16
#define MAX_SAMPLE_DATA    10

int main(int argc, const char *argv[])
{
	ALLEGRO_SAMPLE *sample_data = 0;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_EVENT event;
	
	al_init();
	al_install_keyboard();
	
	display = al_create_display(640, 480);
	if (!display) {
	}
	
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	al_init_acodec_addon();
	
	if (!al_install_audio()) {
		fprintf(stderr, "Could not init sound!\n");
		return 1;
	}
	
	if (!al_reserve_samples(RESERVED_SAMPLES)) {
		fprintf(stderr, "Could not set up voice and mixer.\n");
		return 1;
	}
	
	sample_data = al_load_sample("C:\\Users\\aldri\\Desktop\\Vault\\Projects\\allegro5-tests\\drum.wav");
	if (!sample_data) {
		fprintf(stderr, "Could not load sample from '%s'!\n", "bazinga");
		return 1;
	}
	
	printf("using driver: %s\n", al_get_audio_driver_specifier());
	
	while (true) {
		al_wait_for_event(event_queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			return 0;
		else if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				break;
			}
			if (event.keyboard.unichar == ' ') {
				al_stop_samples();
			}
			
			al_play_sample(sample_data, 1.0, 0.5, 1.0, ALLEGRO_PLAYMODE_REVERSED, NULL);
		}
	}
	
	/* Sample data and other objects will be automatically freed. */
	al_uninstall_audio();
	
	return 0;
}

/* vim: set sts=3 sw=3 et: */