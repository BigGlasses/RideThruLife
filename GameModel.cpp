#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

#include "GameModel.hpp"


GameModel::GameModel(){
}
GameModel::GameModel(std::string title, objLoader o){
	this->title = title;
	objectData = o.loadObj(title + ".obj");

}