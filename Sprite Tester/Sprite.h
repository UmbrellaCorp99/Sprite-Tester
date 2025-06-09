class sprite
{
public: 
	~sprite();
	void updatesprite();
	void bouncesprite(int SCREEN_W, int SCREEN_H);
	void load_animated_sprite(int size);
	void drawSprite();
	int getX(){return x;}
	int getY(){return y;}
	void collision(sprite sp[], int csize, int current, int width, int height);

private:
	int x,y;
	float angle;
	int r, g, b;
	int width,height;
	int xspeed,yspeed;
	int xdelay,ydelay;
	int xcount,ycount;
	int curframe,maxframe,animdir;
	int framecount,framedelay;
	bool CollisionIsTrue;
	bool specialityPower[4];	//0=Spining, 1= Scared, 2=Baby, 3=Freeze
	ALLEGRO_BITMAP *image[9];
};