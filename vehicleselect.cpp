#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

#include "vehicleselect.hpp"


VehicleSelect::VehicleSelect(){
	vehicleIndex = 0;
}

void VehicleSelect::init(){
	textureLoader tl;
	background = tl.loadTexture("vehicleselect.bmp");
}

void VehicleSelect::draw(){
	glPushMatrix();
	glLoadIdentity();

	//Draw background
	gluOrtho2D(-1, 1, -1, 1);

	glBindTexture(GL_TEXTURE_2D, background);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glColor3f(1, 1, 1);

	glBegin(GL_QUADS);

	glVertex3f(-1, -1, 0);
	glTexCoord2f(0, 1); 

	glVertex3f(-1,  1, 0);
	glTexCoord2f(1, 1); 

	glVertex3f( 1,  1, 0);
	glTexCoord2f(1, 0); 

	glVertex3f( 1, -1, 0);
	glTexCoord2f(0, 0); 

	glEnd();

	glDisable(GL_TEXTURE_2D);

	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	gluPerspective(90, 1280.0/720, 1, 40);
	gluLookAt(0, 5, -10, 0, 0, 0, 0, 1, 0);
	camDir[0] = 0;
	camDir[1] = -4;
	camDir[2] = 10;

	glUseProgram(shaderProgram2);
	glTranslatef(vehicleIndex*10, 0, 0);
	updateLightMatrices();
	updateShadowMatrices();
	for (int i = 0; i < vehicleNum; i++){
		if (i == vehicleIndex){
			//glPushMatrix();
			glRotatef(rotation, 0, 1.0, 0);
			updateShadowMatrices();
			gms[i].draw();
			glRotatef(-rotation, 0, 1.0, 0);
			//glPopMatrix();
		}
		else{
			updateShadowMatrices();
			gms[i].draw();
		}
		glTranslatef(-10, 0, 0);
	}
	glUseProgram(0);

}

void VehicleSelect::update(){
	rotation = (rotation + 1) % 360;
}

bool VehicleSelect::selected(){
	return finished;
}

std::string VehicleSelect::selectedVehicleName(){
	//std::cout << gms[vehicleIndex].title;
	return gms[vehicleIndex].title;
}

void VehicleSelect::keyboard(unsigned char key, int xIn, int yIn)
{
	// cam.keyPressed(key);
	switch (key)
	{
		case 'a':
			vehicleIndex -= 1;
			if (vehicleIndex < 0) vehicleIndex = 0;
			break;

		case 'd':
			vehicleIndex += 1;
			if (vehicleIndex >= vehicleNum) vehicleIndex = vehicleNum - 1;
			break;

		case 'w':
			finished = true;
			break;
	}
}