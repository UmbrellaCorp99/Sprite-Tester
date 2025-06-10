//Alexander Young
//Lab 10

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include "Sprite.h"

#include <iostream>
using namespace std;

//This function draws a sprite to the display. A sprite can either rotate around its center, 
// scale in half upon every collision with another sprite, change colors upon collision with another sprite,
// or freeze for 5 seconds upon collision with another sprite
//Takes no parameters
//No return
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
	else if (specialityPower[2]) {
		if (CollisionIsTrue) {
			if (!scaled) {
				scaled = true;
				startTime = al_get_time();
				al_draw_scaled_bitmap(image[curframe], 0, 0, al_get_bitmap_width(image[0]), al_get_bitmap_height(image[0]), x, y, width / 2, height / 2, 0);
				width = width / 2;
				height = height / 2;
			}
			else {
				endTime = al_get_time();
				if (endTime - startTime >= 10) {
					scaled = false;
					al_draw_scaled_bitmap(image[curframe], 0, 0, al_get_bitmap_width(image[0]), al_get_bitmap_height(image[0]), x, y, originalWidth, originalHeight, 0);
					width = originalWidth;
					height = originalHeight;
				}
				else {
					al_draw_scaled_bitmap(image[curframe], 0, 0, al_get_bitmap_width(image[0]), al_get_bitmap_height(image[0]), x, y, width / 2, height / 2, 0);
					width = width / 2;
					height = height / 2;
				}
			}
		}
		else {
			al_draw_scaled_bitmap(image[curframe], 0, 0, al_get_bitmap_width(image[0]), al_get_bitmap_height(image[0]), x, y, width, height, 0);
		}
	}
	else if (specialityPower[3] && CollisionIsTrue) {
		if (!paused) {
			paused = true;
			startTime = al_get_time();
		}
		else if (paused) {
			endTime = al_get_time();
			if ((endTime - startTime) >= 5.0) {
				paused = false;
				al_draw_bitmap(image[curframe], x, y, 0);
			}
		}
	}
	CollisionIsTrue = false;
}

//This function updates a sprite's x and y location
//Takes no parameters
//No return
void sprite::updatesprite()
{
	//update x position
	if (!paused) {
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
}

//This function changes a sprites direction upon colliding with a display boundary
//Takes two integers representing a display width and height as parameters
//No return
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

//This function loads all the images of a split gif into a bitmap and randomly assigns it a special power (rotating, scaling, changing color, freezing)
//Takes an integer representing the number of images of the gif to use
//No return
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
	originalWidth = al_get_bitmap_width(image[0]);
	originalHeight = al_get_bitmap_height(image[0]);
	width=al_get_bitmap_width(image[0]);
	height=al_get_bitmap_height(image[0]);
	curframe = 0;
	framedelay = 4;
	framecount = 0;
	angle = 0;
	paused = false;
	scaled = false;
	r = 255, g = 255, b = 255;
	for (int i = 0; i < 4; i++) {
		specialityPower[i] = false;
	}
	int sp = rand() % 4;
	specialityPower[sp] = true;
	CollisionIsTrue = false;
}

//This function detects if a collision occurs between sprites
//Takes an array of sprites, an integer representing the number of sprites, an integer representing the index of the sprite being checked,
//and two integers representing the display width and height
//No return
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

//This is a deconstructor for the sprite class that destroys every sprite object
//Takes no parameter
//No return
sprite::~sprite()
{
	for(int i = 0; i < maxframe; i++)
		al_destroy_bitmap(image[i]);
}



