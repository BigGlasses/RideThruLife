#ifndef GameModel_H
#define GameModel_H

#include "OpenGLImports.hpp"
#include "objLoader.hpp"
#include "textureLoader.hpp"

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
		GameModel(std::string title);
		void draw();
	private:
		GLfloat* objectData;
		GLuint dataBuffer;
		std::string title;
		int* numVertices;
		GLuint textureID;
};


#endif