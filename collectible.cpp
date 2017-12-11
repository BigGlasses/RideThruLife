#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

#include "collectible.hpp"

//lifeTime = 0;

collectible::collectible(float Inx, float Iny, float Inz, int life)
{
	x = Inx;
	y = Iny;
	z = Inz;
	life = lifeTime;
}

float collectible::getX()
{
	return x;
}

float collectible::getY()
{
	return y;
}

float collectible::getZ()
{
	return z;
}

void collectible::canBeCollected(float Inx, float Iny, float Inz)
{
	float threshold = 0.1;
	if(Inx < x + threshold && Inx > x - threshold)
		if(Iny < y + threshold && Iny > y - threshold)
			if(Inx < z + threshold && Inz > z - threshold)
			{
				//Horrible checking
			}
}

void collectible::isClose(float Inx, float Iny, float Inz)
{
	float threshold = 10.0;
	if(Inx < x + threshold && Inx > x - threshold)
		if(Iny < y + threshold && Iny > y - threshold)
			if(Inx < z + threshold && Inz > z - threshold)
			{
				//Horrible checking
			}
}

void collectible::update()
{
	lifeTime -= 1;
	if(lifeTime <= 0)
	{
		//Something happens?
	}
}



