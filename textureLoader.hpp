#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "OpenGLImports.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>


class textureLoader{
	public:
		textureLoader();
		GLuint loadTextureFromFile( std::string path);
		GLuint loadTexture(std::string fileName);
};


#endif