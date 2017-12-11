#ifndef GameModel_H
#define GameModel_H

#include "OpenGLImports.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>


class GameModel{
	public:
		GameModel();
		GameModel::GameModel(std::string title, objLoader o);
	private:
		GLfloat* objectData;
		std::string title;
};


#endif