#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <ifstream>
#include <ofstream>
#include <iostream>
#include <list>

#include "objLoader.hpp"

using namespace std;

objLoader::objLoader(){

}
GLfloat* objLoader::loadObjFromFile(string filename){
	int numVertices = 0;
	int numRecords = 24; 
	vector<float> colour[4] = {1.0,1.0,1.0,1.0};

	//3 + 4 + 2 + 3 + 4 + 4 + 1
	// Vertex + Colour + Texture + normals + Material Specular + Material Diffuse + Material Shininess
	GLfloat *vertex_data = (GLfloat *)malloc(sizeof(GLfloat) * (numVertices * numRecords));
	
	ifstream in(filename);
	if (!in) {
		cout << "Invalid file";
	}

	float value;
	float obj_values[24];
	while (in >> value) {
		obj_values.append(value);
	}

	return obj_values;

};

GLfloat*  objLoader::loadObj(std::string fileName){
	//Given "example.obj", open "GameAssets/obj/example.obj" using loadTextureFromFile;
	//Don't forget the mtl file
	return this->loadObjFromFile(fileName);
};
