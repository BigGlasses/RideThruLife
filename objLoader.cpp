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

GLfloat* objLoader::loadObjFromFile(const char* filename, int* n){
	
	printf(filename);
	printf("\n");
	ifstream in(filename);

	int numData = -1;
	int numRecords = 16; 
	float number;
	char c;

	if (!in) {
		cout << "Invalid file";
	}
	
	while(!in.eof()) {
		in.get(c);
		if (c == ' ') {
			numData += 1;
		}
	}
	//printf("%i\n", numData);


	//3 + 4 + 2 + 3 + 4 + 4 + 1
	// Vertex + Colour + Texture + normals + Material Specular + Material Diffuse + Material Shininess
	GLfloat *vertex_data = (GLfloat *)malloc(sizeof(GLfloat) * (numData));
	in.clear();
	in.seekg(0, ios::beg);
	n[0] = numData;
	int i = 0;
	while (in >> number) {
		//for (int i = 0; i < numVertices; i++) {
		vertex_data[i] = number;
		//}
		i++;
	}


	return vertex_data;
};

GLfloat*  objLoader::loadObj(const char* path, int* n){
	//Given "example.obj", open "GameAssets/obj/example.obj" using loadTextureFromFile;
	//Don't forget the mtl file
	std::string s = path;
	return this->loadObjFromFile(("GameAssets/obj/" + s).c_str(), n);
};
