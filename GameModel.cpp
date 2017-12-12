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

GLfloat dataTest[] = {-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.0f, 0.0f, 0.0f, 1.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.0f, 0.0f, 0.0f, 1.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.25f, 0.0f, 0.0f, 1.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.25f, 0.0f, 0.0f, 1.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.0f, 0.0f, 0.0f, 1.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.25f, 0.0f, 0.0f, 1.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.25f, 0.0f, 1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.25f, 0.0f, 1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.5f, 0.0f, 1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.5f, 0.0f, 1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.25f, 0.0f, 1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.5f, 0.0f, 1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.5f, 0.0f, 0.0f, -1.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.5f, 0.0f, 0.0f, -1.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.75f, 0.0f, 0.0f, -1.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.75f, 0.0f, 0.0f, -1.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.5f, 0.0f, 0.0f, -1.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.75f, 0.0f, 0.0f, -1.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.75f, 0.0f, -1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.75f, 0.0f, -1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 1.0f, 0.0f, -1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 1.0f, 0.0f, -1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.75f, 0.0f, -1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 1.0f, 0.0f, -1.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.0f, 1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.875f, 0.0f, 1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.25f, 1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.625f, 0.25f, 1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.875f, 0.0f, 1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.875f, 0.25f, 1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.125f, 0.0f, -1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.0f, -1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.125f, 0.25f, -1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.125f, 0.25f, -1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.0f, -1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.375f, 0.25f, -1.0f, 0.0f, 0.0f, 18.0f, 1.0f, 0.0f, 0.0f};
	
GameModel::GameModel(std::string title, objLoader o){
	this->title = title;
	//objectData = o.loadObj(title + ".obj");
	objectData = dataTest;
	glGenBuffers(1, &dataBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(&objectData), &objectData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void GameModel::draw(){
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);

	int stride = 3 + 4 + 2 + 3 + 3 + 3 + 1;
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0 );

	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)0 );

	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)0 );

	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)0 );

	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, stride, (void*)0 );

	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, stride, (void*)0 );

	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, stride, (void*)0 );


	glDrawArrays(GL_TRIANGLES, 0, sizeof(&objectData)/3);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);

}
