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

bool collectible::canBeCollected(float Inx, float Iny, float Inz)
{
	float threshold = 0.1;
	float dx = Inx - x;
	float dy = Iny - y;
	float dz = Inz - z;

	float distance = dx*dx + dy*dy + dz*dz;
	return distance < threshold * threshold;
}

bool collectible::isClose(float Inx, float Iny, float Inz)
{
	float threshold = 10.0;
	float dx = Inx - x;
	float dy = Iny - y;
	float dz = Inz - z;

	float distance = dx*dx + dy*dy + dz*dz;
	return distance < threshold * threshold;
}

void collectible::update()
{
	lifeTime -= 1;
	if(lifeTime <= 0)
	{
		//Something happens?
	}
}



