#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

#include "GameModel.hpp"

objLoader k;

GLfloat dataTest[] = {-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.0f, 0.0f, 0.0f, 1.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.0f, 0.0f, 0.0f, 1.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.25f, 0.0f, 0.0f, 1.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.25f, 0.0f, 0.0f, 1.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.0f, 0.0f, 0.0f, 1.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.25f, 0.0f, 0.0f, 1.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.25f, 0.0f, 1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.25f, 0.0f, 1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.5f, 0.0f, 1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.5f, 0.0f, 1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.25f, 0.0f, 1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.5f, 0.0f, 1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.5f, 0.0f, 0.0f, -1.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.5f, 0.0f, 0.0f, -1.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.75f, 0.0f, 0.0f, -1.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.75f, 0.0f, 0.0f, -1.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.5f, 0.0f, 0.0f, -1.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.75f, 0.0f, 0.0f, -1.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.75f, 0.0f, -1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.75f, 0.0f, -1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 1.0f, 0.0f, -1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 1.0f, 0.0f, -1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.75f, 0.0f, -1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 1.0f, 0.0f, -1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.0f, 1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.875f, 0.0f, 1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.25f, 1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.25f, 1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.875f, 0.0f, 1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.875f, 0.25f, 1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.125f, 0.0f, -1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.0f, -1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.125f, 0.25f, -1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.125f, 0.25f, -1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.0f, -1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.25f, -1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f};
	

GameModel::GameModel(){
	this->title = title;
	// objectData = k.loadObj((title + ".obj").c_str());
	//objectData = &dataTest;

	//printf("%d\n", sizeof(&objectData));
	// glGenBuffers(1, &dataBuffer);
	// glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(&objectData), &objectData, GL_STATIC_DRAW);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GameModel::GameModel(std::string title, objLoader o){
	this->title = title;
	int *n = new int[1];

	int *numVertices = new int[1]; //15 is stride
	numVertices[0]= n[0]/15;

	objectData = o.loadObj((title + ".txt").c_str(), n);
	//objectData = dataTest;
	glGenBuffers(1, &dataBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*n[0], objectData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GameModel::draw(){
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);

	int stride = (3 + 3 + 2 + 3 + 3 + 1) * sizeof(GL_FLOAT);
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(GL_FLOAT)) );

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,  (GLvoid*)(6 * sizeof(GL_FLOAT)) );

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride,  (GLvoid*)(8 * sizeof(GL_FLOAT)) );

	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, stride,  (GLvoid*)(9 * sizeof(GL_FLOAT)) );

	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, stride,  (GLvoid*)(12 * sizeof(GL_FLOAT)) );


	//printf("%d\n", sizeof(*objectData));
	glDrawArrays(GL_TRIANGLES, 0, numVertices[0]);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
}
