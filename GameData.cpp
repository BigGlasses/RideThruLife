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
GLuint shaderProgram1;
GLuint shaderProgram2;

GLuint mvMatrixLoc;
GLuint pMatrixLoc;
GLuint mvMatrixShadowLoc;
GLuint pMatrixShadowLoc;
GLuint mvMatrixLightLoc;
GLuint pMatrixLightLoc;

GLuint normalTexLoc;
GLuint shadowTexLoc;
GLuint camDirLoc;
GLuint lightDirLoc;

GLuint timeLoc;
GLfloat  modelViewMatrix[16]; 
GLfloat  projectionMatrix[16]; 
GLfloat  modelViewLightMatrix[16]; 
GLfloat  projectionLightMatrix[16]; 

float camPos[] = {0, 0, 3.42f};	//where the camera is
float lightPos[] = {5, 5, 5};
float camDir[] = {1, 1, 1};

shaderLoader shaderLoading;
float timePassed = 0;
const int vehicleNum = 8;
int FPS = 60;
//Window size
int WINDOWX = 1280;
int WINDOWY = 720;
bool updateLights;

void tickTime(){
	timePassed += 1/((float)FPS);
	while ( timePassed > 1 ) timePassed -= 1;
}

void loadAssets(){
	vehicleNames.push_back("car");
	vehicleNames.push_back("dinner_table");
	vehicleNames.push_back("christmas_tree");
	vehicleNames.push_back("balloon");
	vehicleNames.push_back("bike");
	vehicleNames.push_back("grill");
	vehicleNames.push_back("hot_air_balloon");
	vehicleNames.push_back("row_boat");


	for (int i=0; i < vehicleNames.size(); i++) {
		gms.push_back(GameModel(vehicleNames[i]));
	}
}



//Prepares the shader.
	void prepareShaders(){
		shaderProgram1 = glCreateProgram();
		GLuint vertexShader = shaderLoading.loadShaderFromFile( "shaders/testshader.vert", GL_VERTEX_SHADER );
		glAttachShader( shaderProgram1, vertexShader );
		GLuint fragmentShader = shaderLoading.loadShaderFromFile( "shaders/testshader.frag", GL_FRAGMENT_SHADER );
		glAttachShader( shaderProgram1, fragmentShader );
		glLinkProgram( shaderProgram1 );

		shaderProgram2 = glCreateProgram();
		vertexShader = shaderLoading.loadShaderFromFile( "shaders/shadowShader.vert", GL_VERTEX_SHADER );
		glAttachShader( shaderProgram2, vertexShader );
		fragmentShader = shaderLoading.loadShaderFromFile( "shaders/shadowShader.frag", GL_FRAGMENT_SHADER );
		glAttachShader( shaderProgram2, fragmentShader );
		glLinkProgram( shaderProgram2 );



    //Get uniforms
		mvMatrixLoc = glGetUniformLocation(shaderProgram1, "mvMatrix");
		pMatrixLoc = glGetUniformLocation(shaderProgram1, "pMatrix");
		timeLoc = glGetUniformLocation(shaderProgram1, "time");
		mvMatrixShadowLoc = glGetUniformLocation(shaderProgram2, "mvMatrix");
		pMatrixShadowLoc = glGetUniformLocation(shaderProgram2, "pMatrix");
		mvMatrixLightLoc = glGetUniformLocation(shaderProgram2, "mvLightMatrix");
		pMatrixLightLoc = glGetUniformLocation(shaderProgram2, "pLightMatrix");
		normalTexLoc = glGetUniformLocation(shaderProgram2, "normalTexture");
		shadowTexLoc = glGetUniformLocation(shaderProgram2, "shadowTexture");
		lightDirLoc = glGetUniformLocation(camDirLoc, "lightDir");
		camDirLoc = glGetUniformLocation(lightDirLoc, "camDir");

	}

void focusOnLights(){
	updateLights = true;
}

void focusOnShadows(){
	updateLights = false;
}


//Updates the modelview and projection matrix variables.
void updateShadowMatrices(){
	glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);  
	glUniformMatrix4fv(mvMatrixShadowLoc,  1, GL_FALSE, modelViewMatrix);
	glUniformMatrix4fv(pMatrixShadowLoc,  1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(mvMatrixLightLoc,  1, GL_FALSE, modelViewLightMatrix);
	glUniformMatrix4fv(pMatrixLightLoc,  1, GL_FALSE, projectionLightMatrix);
	glUniform1f(timeLoc, timePassed);
	glUniform1i(normalTexLoc, 0);
	glUniform1i(shadowTexLoc, 1);
	glUniform3f(camDirLoc, camDir[0], camDir[1], camDir[1]);
	glUniform3f(lightDirLoc, 1, -1, 1);
}

//Updates the modelview and projection matrix variables.
void updateLightMatrices(){
	glGetFloatv(GL_PROJECTION_MATRIX, projectionLightMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelViewLightMatrix);  
	glUniformMatrix4fv(mvMatrixLoc,  1, GL_FALSE, modelViewLightMatrix);
	glUniformMatrix4fv(pMatrixLoc,  1, GL_FALSE, projectionLightMatrix);
	glUniform1f(timeLoc, timePassed);
}

void updateMatrices(){
	if (updateLights){
		updateLightMatrices();
	}
	else{
		updateShadowMatrices();
	}
}
