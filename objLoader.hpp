#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "OpenGLImports.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

class objLoader{
	public:
		objLoader();
		GLfloat* loadObj(const char* fileName);
	private:
		GLfloat* loadObjFromFile(const char* path);
};


#endif