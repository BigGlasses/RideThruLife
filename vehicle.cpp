#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

#include "Vehicle.hpp"
#include "GameModel.hpp"
#include "GameData.hpp"
#define PI 3.14159265


//Gaint constructor, sorry
Vehicle::Vehicle(){}
Vehicle::Vehicle(float Inx, float Iny, float Inz, float Inacceleration, float Inturning, float Inbrakes, float InfuelEfficency, float Inscale,bool InisBoat, GameModel InModel){
	x = Inx;
	y = Iny;
	z = Inz;
	scale = Inscale;
	acceleration = Inacceleration;
	turning = Inturning;
	brakes = Inbrakes;
	fuelEfficency = InfuelEfficency;
	isBoat = InisBoat;
	model = InModel;
}

//Many accessors
float Vehicle::getX()
{
	return x;
}

float Vehicle::getY()
{
	return y;
}

float Vehicle::getScale()
{
	return scale;
}

float Vehicle::getZ()
{
	return z;
}

float Vehicle::getSpeedX()
{
	return speedX;
}

float Vehicle::getSpeedY()
{
	return speedY;
}

float Vehicle::getSpeedZ()
{
	return speedZ;
}

float Vehicle::getAcceleration()
{
	return acceleration;
}

void Vehicle::shouldTurn(bool val){
	isTurning = val;
}
float Vehicle::getTurning()
{
	return turning;
}

float Vehicle::getBrakes()
{
	return brakes;
}

float Vehicle::getfuelEfficency()
{
	return fuelEfficency;
}

bool Vehicle::getBoat()
{
	return isBoat;
}

float Vehicle::getRotation()
{
	return rotation;
}

float Vehicle::getTilt()
{
	return tilt;
}

float Vehicle::getRoll()
{
	return roll;
}

GameModel Vehicle::getModel()
{
	return model;
}

//Set accelereating
void Vehicle::accelerate(bool state)
{
	isAccelerating = state;
}

//Rotate, true for positive false for negitave
//Rotation is 0-360.  Assuming this would be used on the x-Plane.  Don't know if we want other rotations? (y,z)?
void Vehicle::turn(bool direction)
{
	if(isTurning){
		if(direction){
			angularX += turning;
		}
		else{
			angularX -= turning;
		}
	}
}

void Vehicle::ChangeTilt(bool direction, float mag)
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

void Vehicle::ChangeRoll(bool direction, float mag)
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
void Vehicle::brake(bool state){
	isBraking = state;
}

float Vehicle::getTrailX(int i){
	return trail[(trailIndex + i) % vehicleTrailLength][0];
}

float Vehicle::getTrailY(int i){
	return trail[(trailIndex + i) % vehicleTrailLength][1];
}

float Vehicle::getTrailZ(int i){
	return trail[(trailIndex + i) % vehicleTrailLength][2];
}

void Vehicle::jump(){
	if (y <= 0 && momentumY <= 0)
		momentumY += fuelEfficency*4;
}

void Vehicle::update(){
	trail[trailIndex][0] = x;
	trail[trailIndex][1] = y;
	trail[trailIndex][2] = z;
	trailIndex = (trailIndex - 1) % vehicleTrailLength;
	if (trailIndex < 0) trailIndex = vehicleTrailLength - 1;

	//Updates speeds
	if(isAccelerating)
	{
		speedX += sin(rotation * PI / 180.0 ) * acceleration/10.0;
		speedZ += cos(rotation * PI / 180.0 ) * acceleration/10.0;
	}
	if(isBraking)
	{
		speedX -= sin(rotation * PI / 180.0 ) * brakes/10.0;
		speedZ -= cos(rotation * PI / 180.0 ) * brakes/10.0;
	}

	//Update Spin
	rotation += angularX/5.0;
	angularX *= 0.9;
	if(rotation > 360)
		rotation = static_cast<int>(rotation) % 360;
	//Fix underflow
	if(rotation < 0)
		rotation = rotation + 360;

	speedX *= 0.9; //drag
	speedZ *= 0.9; //drag	
	//Update position
	momentumX += 0.2 * -(x - getTrailX(1)) + speedX/10.0;
	momentumY += 0.2 * -(y - getTrailY(1)) + speedY/10.0;
	momentumZ += 0.2 * -(z - getTrailZ(1)) + speedZ/10.0;

	momentumX *= 0.95;
	momentumY *= 0.95;
	momentumZ *= 0.95;
	momentumY -= 0.15;

	x += momentumX;
	y += momentumY;
	z += momentumZ;

	if (y < 0){
		y = 0;
		momentumY = 0;
	}
}

void Vehicle::draw(bool render){
	glTranslatef(x, y, z);
	glRotatef(rotation, 0, 1.0, 0);

	if (abs(momentumZ) + abs(momentumY) + abs(momentumX) > 0){
		float moment = sqrt(momentumZ*momentumZ + momentumX*momentumX + momentumY*momentumY);
		glRotatef(-360*(momentumY/(5 + moment)), 1.0, 0, 0);
		glRotatef(-60*(angularX)/(35 * (1 + moment)), 0, 0, 1.0);
	}

	updateMatrices();
	if (render) model.draw();
}