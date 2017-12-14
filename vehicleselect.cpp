#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

#include "vehicleselect.hpp"


//Gaint constructor, sorry
VehicleSelect::VehicleSelect(){
	vehicleIndex = 0;

}

void VehicleSelect::draw(){
	for (int i = 0; i < vehicleNum; i++){
		
	}
}

void VehicleSelect::keyboard(unsigned char key, int xIn, int yIn)
{
	// cam.keyPressed(key);
	switch (key)
	{
		case 'a':
		vehicleIndex = (vehicleIndex - 1)%vehicleNum;
		break;

		case 'd':
		vehicleIndex = (vehicleIndex + 1)%vehicleNum;
		break;
	}
}