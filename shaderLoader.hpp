#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include "OpenGLImports.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

class shaderLoader
{
	public:
		shaderLoader();
		GLuint loadShaderFromFile(std::string path, GLenum shaderType);
	
};


#endif