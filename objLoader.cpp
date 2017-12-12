#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>
#include <list>

#include "objLoader.hpp"

using namespace std;

objLoader::objLoader(){}

GLfloat* objLoader::loadObjFromFile(const char* filename){
	int numVertices = 0;
	int numRecords = 24; 

	//3 + 4 + 2 + 3 + 4 + 4 + 1
	// Vertex + Colour + Texture + normals + Material Specular + Material Diffuse + Material Shininess
	GLfloat *vertex_data = (GLfloat *)malloc(sizeof(GLfloat) * (numVertices * numRecords));
	
	ifstream in(filename);

	float number;
	char c;

	if (!in) {
		cout << "Invalid file";
	}
	
	while(!in.eof()) {
		in.get(c);
		if (c == ' ') {
			numVertices += 1;
		}
	}

	while (in >> number) {
		for (int i = 0; i < numVertices; ++i) {
			vertex_data[i] = number;
		}
	}

	return vertex_data;
};

GLfloat*  objLoader::loadObj(const char* path){
	//Given "example.obj", open "GameAssets/obj/example.obj" using loadTextureFromFile;
	//Don't forget the mtl file
	return this->loadObjFromFile(path);
};
