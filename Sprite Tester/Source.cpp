//Alexander Young
//Lab 10

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Sprite.h"
#include <iostream>
using namespace std;

int main(void)
{
	//variables
	int width = 640;
	int height = 480;
	bool done = false;
	const int NUMalien = 5;
	bool redraw = true;
	const int FPS = 60;


	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	sprite alien[NUMalien];
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT* font = NULL;

	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if(!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	timer = al_create_timer(1.0 / FPS);

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_set_target_bitmap(al_get_backbuffer(display));
	al_start_timer(timer);
	srand(time(NULL));

	font = al_load_font("Movistar Text Regular.ttf", 24, 0);

	for (int i = 0; i < NUMalien; i++) {
		alien[i].load_animated_sprite(9);
	}
	

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			//check for screen collision for every sprite
			for (int i = 0; i < NUMalien; i++) {
				alien[i].bouncesprite(width, height);
			}
			//check for collision with other sprites for every sprite
			for (int i = 0; i < NUMalien; i++) {
				alien[i].collision(alien, NUMalien, i, width, height);
			}
			
			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;

		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue))
		{


			redraw = false; 
			//update every sprite's location
			for (int i = 0; i < NUMalien; i++) {
				alien[i].updatesprite();
			}
			//draw every sprite in the new location
			for (int i = 0; i < NUMalien; i++) {
				alien[i].drawSprite();
			}
			//if a sprite's dimensions are less than 1 (it disappeared) than print a message
			for (int i = 0; i < NUMalien; i++) {
				if (alien[i].getWidth() < 1 || alien[i].getHeight() < 1) {
					al_draw_text(font, al_map_rgb(255, 255, 0), width/2, height/2, 0, "A sprite has died");
				}
			}
			
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_font(font);

	return 0;
}


