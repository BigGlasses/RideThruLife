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

	glUseProgram(shaderProgram2);
	glTranslatef(-vehicleIndex, 0, 0);
	updateLightMatrices();
	updateShadowMatrices();
	for (int i = 0; i < vehicleNum; i++){
		glTranslatef(1, 0, 0);
		if (i == vehicleIndex){
			glPushMatrix();
			glRotatef(rotation, 0, 1.0, 0);
			updateShadowMatrices();
			gms[i].draw();
			glPopMatrix();
		}
		else{
			updateShadowMatrices();
			gms[i].draw();
		}
	}
	glUseProgram(0);

}

void VehicleSelect::update(){
	rotation = (rotation + 1) % 360;
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