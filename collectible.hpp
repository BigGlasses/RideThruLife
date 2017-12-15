#ifndef Collectible_H
#define Collectible_H

#include "OpenGLImports.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

#include "GameModel.hpp"
#include "GameData.hpp"

class Collectible{
	public:
		Collectible(float Inx, float Iny, float Inz, int life, GameModel Inmodel);
		bool canBeCollected(float Inx, float Iny, float Inz);
		bool isClose(float Inx, float Iny, float Inz);
		void update();
		float getX();
		float getY();
		float getZ();
		float draw(bool render);
		GameModel getModel();

	private:
		GameModel model;
		int lifeTime = 0;
		float x = 0.0;
		float y = 0.0;
		float z = 0.0;
};


#endif