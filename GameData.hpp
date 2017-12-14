#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "OpenGLImports.hpp"
#include "objLoader.hpp"
#include "textureLoader.hpp"
#include "GameModel.hpp"

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
void loadAssets();




#endif