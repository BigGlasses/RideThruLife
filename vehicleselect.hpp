#ifndef VEHICLESELECT_H
#define VEHICLESELECT_H

#include "OpenGLImports.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

#include "GameModel.hpp"


class VehicleSelect{
	public:
		Vehicle(float Inx, float Iny, float Inz, float acceleration, float turning, float brakes, float fuelEfficency, bool isBoat, GameModel Inmodel);
		void draw();
		void keyboard(unsigned char key, int xIn, int yIn);

	private:
		int vehicleIndex;
};


#endif