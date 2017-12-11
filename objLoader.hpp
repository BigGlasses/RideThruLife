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


class objLoader{
	public:
		objLoader();
		GLfloat* loadObj(std::string fileName);
	private:
		GLfloat* loadObjFromFile( std::string path);
};


#endif