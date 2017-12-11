#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "OpenGLImports.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>


class collectible{
	public:
		collectible(float Inx, float Iny, float Inz, int life);
		void canBeCollected(float Inx, float Iny, float Inz);
		void isClose(float Inx, float Iny, float Inz);
		void update();
		float getX();
		float getY();
		float getZ();

	private:
		int lifeTime = 0;
		float x = 0.0;
		float y = 0.0;
		float z = 0.0;
};


#endif