#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>

#include "objLoader.hpp"


objLoader::objLoader(){

}
GLfloat* objLoader::loadObjFromFile( std::string path){
	int numVertices = 0;
	int numRecords = 24; 
	//3 + 4 + 2 + 3 + 4 + 4 + 4
	// Vertex + Colour + Texture + Material Specular + Material Diffuse + Material Shininess
	GLfloat *vertex_data = (GLfloat *)malloc(sizeof(GLfloat) * (numVertices * numRecords));
	return vertex_data;
};

GLfloat*  objLoader::loadObj(std::string fileName){
	//Given "example.obj", open "GameAssets/obj/example.obj" using loadTextureFromFile;
	//Don't forget the mtl file
	return this->loadObjFromFile("example.obj");
};