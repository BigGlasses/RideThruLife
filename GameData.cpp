#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

#include "GameData.hpp"

std::vector<GameModel> gms;
std::vector<std::string> vehicleNames; 

void loadAssets(){
	vehicleNames.push_back("car");
	vehicleNames.push_back("dinner_table");
	vehicleNames.push_back("christmas_tree");
	vehicleNames.push_back("balloon");
	vehicleNames.push_back("bike");
	vehicleNames.push_back("balloon");
	vehicleNames.push_back("grill");



	for (int i=0; i < vehicleNames.size(); i++) {
		gms.push_back(GameModel(vehicleNames[i]));
	}
}