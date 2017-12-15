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


class Vehicle{
	public:
		Vehicle();
		Vehicle(float Inx, float Iny, float Inz, float acceleration, float turning, float brakes, float fuelEfficency, bool isBoat, GameModel Inmodel);
		void update();
		void draw();
		void accelerate(bool state);
		void turn(bool direction);
		void jump();
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
		void shouldTurn(bool val);
		float getTrailX(int i);
		float getTrailY(int i);
		float getTrailZ(int i);
		GameModel getModel();

	private:
		float x = 0.0;
		float y = 0.0;
		float z = 0.0;
		float speedX = 0.0;
		float speedY = 0.0;
		float speedZ = 0.0;

		float angularX = 0.0;
		float angularY = 0.0;
		float angularZ = 0.0;

		float momentumX = 0.0;
		float momentumY = 0.0;
		float momentumZ = 0.0;

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
		bool isTurning = false;
		static const int vehicleTrailLength = 120;
		int trailIndex = 0;
		float trail[vehicleTrailLength][3];

		GameModel model;
};




#endif