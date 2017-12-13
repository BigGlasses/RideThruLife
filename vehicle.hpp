#ifndef VEHICLE_H
#define VEHICLE_H

#include "OpenGLImports.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

#include "GameModel.hpp"


class vehicle{
	public:
		vehicle(float Inx, float Iny, float Inz, float acceleration, float turning, float brakes, float fuelEfficency, bool isBoat, GameModel Inmodel);
		void update();
		void accelerate(bool state);
		void turn(bool direction);
		void ChangeTilt(bool direction, float mag);
		void ChangeRoll(bool direction, float mag);
		void brake(bool state);
		float getX();
		float getY();
		float getZ();
		float getSpeedX();
		float getSpeedY();
		float getSpeedZ();
		float getAcceleration();
		float getTurning();
		float getBrakes();
		float getfuelEfficency();
		bool getBoat();
		float getRotation();
		float getTilt();
		float getRoll();
		GameModel getModel();

	private:
		float x = 0.0;
		float y = 0.0;
		float z = 0.0;
		float speedX = 0.0;
		float speedY = 0.0;
		float speedZ = 0.0;
		float acceleration = 0.0;
		float rotation = 0.0;
		float tilt = 0.0;
		float roll = 0.0;
		float turning = 0.0;
		float brakes = 0.0;
		float fuelEfficency = 0.0;
		bool isBoat = false;
		bool isAccelerating = false;
		bool isBraking = false;
		GameModel model;
};


#endif