#pragma once

struct Animation
{
	int frames = 1;
	int speed = 100;
	int width = 32;
	int height = 32;

	Animation()  = default;
	Animation(int f, int s, int w, int h)
	{
		frames = f;
		speed = s;
		width = w;
		height = h;
	}


};
