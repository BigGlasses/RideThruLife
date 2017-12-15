#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

#include "Collectible.hpp"
#include "GameModel.hpp"

//lifeTime = 0;

Collectible::Collectible(float Inx, float Iny, float Inz, int life, GameModel Inmodel)
{
	x = Inx;
	y = Iny;
	z = Inz;
	life = lifeTime;
	model = Inmodel;
}

float Collectible::getX()
{
	return x;
}

float Collectible::getY()
{
	return y;
}
float Collectible::draw(bool render)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(4, 4, 4);
	glRotatef(lifeTime, 0, 1.0, 0);
	updateMatrices();
	if (render) model.draw();
	glPopMatrix();
}

float Collectible::getZ()
{
	return z;
}

GameModel Collectible::getModel()
{
	return model;
}

bool Collectible::canBeCollected(float Inx, float Iny, float Inz)
{
	float threshold = 10.0;
	float dx = Inx - x;
	float dy = Iny - y;
	float dz = Inz - z;

	float distance = dx*dx + dy*dy + dz*dz;
	return distance < threshold * threshold;
}

bool Collectible::isClose(float Inx, float Iny, float Inz)
{
	float threshold = 10.0;
	float dx = Inx - x;
	float dy = Iny - y;
	float dz = Inz - z;

	float distance = dx*dx + dy*dy + dz*dz;
	return distance < threshold * threshold;
}

void Collectible::update()
{
	lifeTime -= 1;
	if(lifeTime <= 0)
	{
		//Something happens?
	}
}



