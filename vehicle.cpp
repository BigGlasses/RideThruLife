#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

#include "vehicle.hpp"
#include "GameModel.hpp"

//Gaint constructor, sorry
vehicle::vehicle(float Inx, float Iny, float Inz, float Inacceleration, float Inturning, float Inbrakes, float InfuelEfficency, bool InisBoat, GameModel InModel)
{
	x = Inx;
	y = Iny;
	z = Inz;
	acceleration = Inacceleration;
	turning = Inturning;
	brakes = Inbrakes;
	fuelEfficency = InfuelEfficency;
	isBoat = InisBoat;
	model = InModel;
}

//Many accessors
float vehicle::getX()
{
	return x;
}

float vehicle::getY()
{
	return y;
}

float vehicle::getZ()
{
	return z;
}

float vehicle::getSpeedX()
{
	return speedX;
}

float vehicle::getSpeedY()
{
	return speedY;
}

float vehicle::getSpeedZ()
{
	return speedZ;
}

float vehicle::getAcceleration()
{
	return acceleration;
}

float vehicle::getTurning()
{
	return turning;
}

float vehicle::getBrakes()
{
	return brakes;
}

float vehicle::getfuelEfficency()
{
	return fuelEfficency;
}

bool vehicle::getBoat()
{
	return isBoat;
}

float vehicle::getRotation()
{
	return rotation;
}

float vehicle::getTilt()
{
	return tilt;
}

float vehicle::getRoll()
{
	return roll;
}

GameModel vehicle::getModel()
{
	return model;
}

//Set accelereating
void vehicle::accelerate(bool state)
{
	isAccelerating = state;
}

//Rotate, true for positive false for negitave
//Rotation is 0-360.  Assuming this would be used on the x-Plane.  Don't know if we want other rotations? (y,z)?
void vehicle::turn(bool direction)
{
	if(direction)
		rotation += turning;
		//Fix overflow
		if(rotation > 360)
			rotation = static_cast<int>(rotation) % 360;
	else
		rotation -= turning;
		//Fix underflow
		if(rotation < 0)
			rotation = rotation + 360;
}

void vehicle::ChangeTilt(bool direction, float mag)
{
	if(direction)
		tilt += mag;
		if(tilt > 360)
			tilt = static_cast<int>(tilt) % 360;
	else
		tilt -= mag;
		//Fix underflow
		if(tilt < 0)
			tilt = tilt + 360;
}

void vehicle::ChangeRoll(bool direction, float mag)
{
	if(direction)
		roll += mag;
		if(roll > 360)
			roll = static_cast<int>(roll) % 360;
	else
		roll -= mag;
		//Fix underflow
		if(roll < 0)
			roll = roll + 360;
}

//Set braking
void vehicle::brake(bool state)
{
	isBraking = state;
}

void vehicle::update()
{
	//Updates speeds
	if(isAccelerating)
	{
		speedX += sin(rotation) * acceleration;
		speedZ += cos(rotation) * acceleration;
	}
	if(isBraking)
	{
		speedX -= sin(rotation) * brakes;
		speedZ -= cos(rotation) * brakes;
	}

	//Update position
	x += speedX;
	y += speedY;
	z += speedZ;
}