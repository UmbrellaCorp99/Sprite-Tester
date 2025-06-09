#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include "Sprite.h"

#include <iostream>
using namespace std;

void sprite::drawSprite()
{
	if (specialityPower[0]) {
		al_draw_rotated_bitmap(image[curframe], width / 2, height / 2, x, y, angle, 0);
		angle += .1;
	}
	else if (specialityPower[1]) {
		if (CollisionIsTrue) {
			r = rand() % 255;
			g = rand() % 255;
			b = rand() % 255;;
		}
		al_draw_tinted_bitmap(image[curframe], al_map_rgb(r, g, b), x, y, 0);
	}
	else {
		al_draw_bitmap(image[curframe], x, y, 0);
	}
	
	CollisionIsTrue = false;
}

void sprite::updatesprite()
{
	//update x position
	if (++xcount > xdelay)
	{
		xcount = 0;
		x += xspeed;
	}

	//update y position
	if (++ycount > ydelay)
	{
		ycount = 0;
		y += yspeed;
	}


	if (framecount++ > framedelay)
	{
		framecount = 0;
		curframe++;
		if (curframe >= maxframe)
			curframe = 0;
	}
}

void sprite::bouncesprite(int SCREEN_W, int SCREEN_H)
{
	//simple screen bouncing behavior
	if (x < 0)
	{
		x = 0;
		xspeed = rand() % 2 + 4;
		animdir *= -1;
	}

	else if (x > SCREEN_W - width)
	{
		x = SCREEN_W - width;
		xspeed = rand() % 2 - 6;
		animdir *= -1;
	}

	if (y < 0)
	{
		y = 0;
		yspeed = rand() % 2 + 4;
		animdir *= -1;
	}

	else if (y > SCREEN_H - height)
	{
		y = SCREEN_H -  height;
		yspeed = rand() % 2 - 6;
		animdir *= -1;
	}

}

void sprite::load_animated_sprite(int size)
{
	//load the animated sprite
	char s[80];
	maxframe=size;
	for (int n=0; n<size; n++)
	{
		sprintf_s(s,"frame_%d_delay-0.04s.png",n+1);
		image[n] = al_load_bitmap(s);

		al_convert_mask_to_alpha(image[n], al_map_rgb(255, 255, 255));
	}  
	width=al_get_bitmap_width(image[0]);
	height=al_get_bitmap_height(image[0]);
	curframe = 0;
	framedelay = 4;
	framecount = 0;
	angle = 0;
	r = 255, g = 255, b = 255;
	for (int i = 0; i < 4; i++) {
		specialityPower[i] = false;
	}
	int sp = rand() % 2;
	specialityPower[sp] = true;
	CollisionIsTrue = false;
}

void sprite::collision(sprite sp[], int csize, int current, int WIDTH, int HEIGHT)
{
	for (int i = 0; i < csize; i++)
	{
		if (i != current)
			if (x > sp[i].getX()-width && x <= sp[i].getX()+width) {
				if (y >= sp[i].getY()-height && y <= sp[i].getY()+height) {
					x = rand() % WIDTH;
					y = rand() % HEIGHT;
					CollisionIsTrue = true;
				}
			}
	}
}

sprite::~sprite()
{
	for(int i = 0; i < maxframe; i++)
		al_destroy_bitmap(image[i]);
}



