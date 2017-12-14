#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "OpenGLImports.hpp"
#include "objLoader.hpp"
#include "textureLoader.hpp"
#include "GameModel.hpp"
#include "shaderLoader.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>



extern std::vector<GameModel> gms;
extern std::vector<std::string> vehicleNames; 
const int vehicleNum = 7;
extern float timePassed;
extern int FPS;
//Window size
extern int WINDOWX;
extern int WINDOWY;

void loadAssets();

void prepareShaders();

void updateShadowMatrices();

void updateLightMatrices();

void tickTime();

extern shaderLoader shaderLoading;
extern GLuint shaderProgram1;
extern GLuint shaderProgram2;

extern GLuint mvMatrixLoc;
extern GLuint pMatrixLoc;
extern GLuint mvMatrixShadowLoc;
extern GLuint pMatrixShadowLoc;
extern GLuint mvMatrixLightLoc;
extern GLuint pMatrixLightLoc;

extern GLuint normalTexLoc;
extern GLuint shadowTexLoc;

extern GLuint timeLoc;
extern GLfloat  modelViewMatrix[16]; 
extern GLfloat  projectionMatrix[16]; 
extern GLfloat  modelViewLightMatrix[16]; 
extern GLfloat  projectionLightMatrix[16]; 



#endif