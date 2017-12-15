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
#include <iostream>
#include <string>

#include "GameModel.hpp"
#include "GameData.hpp"
#include "textureLoader.hpp"


class VehicleSelect{
	public:
		VehicleSelect();
		void draw();
		void init();
		void update();
		void keyboard(unsigned char key, int xIn, int yIn);
		bool selected();
		void boot();
		std::string selectedVehicleName();

	private:
		int vehicleIndex = 0;
		int rotation = 0;
		GLuint background;
		bool finished = false;

};


#endif