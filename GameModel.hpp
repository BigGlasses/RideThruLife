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
		std::string title;
	private:
		GLfloat* objectData;
		GLuint dataBuffer;
		int numVertices;
		int* n;
		GLuint textureID;
};


#endif