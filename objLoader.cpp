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

	ifstream in(filename);
	if (!in) {
		cout << "Invalid file";
	}

	string line;
	while (getline(in, line)) {

	}
	// int numVertices = 0;
	// int numRecords = 24; 
	// vector<float> colour[4] = {1.0,1.0,1.0,1.0};

	// //3 + 4 + 2 + 3 + 4 + 4 + 1
	// // Vertex + Colour + Texture + normals + Material Specular + Material Diffuse + Material Shininess
	// GLfloat *vertex_data = (GLfloat *)malloc(sizeof(GLfloat) * (numVertices * numRecords));
	
	// //loading objects
	// vector<glm::vec3> obj_verticies;
	// vector<glm::vec4> obj_amb;
	// vector<glm::vec2> obj_texture;
	// vector<glm::vec3> obj_normals;
	// vector<glm::vec3> obj_spec;
	// vector<glm::vec3> obj_dif;
	// float illumination;
	// vector<glm::vec3 translucency;

	// ifstream inObj(path);
	// if (!inObj){
	// 	cout << "Cannot open" << path << endl; exit(1);
	// }

	// string line;
	// while(getline(inObj, line)) {
	// 	if (line.substr(0,2) == "v ") {
    //         istringstream s(line.substr(2));
    //         glm::vec3 v; s >> v.x; s >> v.y; s >> v.z = 1.0f;
	// 		obj_vertices.push_back(v);
	// 		numVertices += 1;
	// 	}else if (line.substr(0,3) == "vt ") {
    //         istringstream s(line.substr(3));
    //         glm::vec2 t; s >> t.x; s >> t.y = 1.0f;
    //         obj_vertices.push_back(t);
	// 	}else if (line.substr(0,3) == "vn ") {
    //         istringstream s(line.substr(3));
    //         glm::vec3 n; s >> n.x; s >> n.y; s >> n.z = 1.0f;
    //         obj_normals.push_back(n);
	// 	}
	// } 

	// ifstream inMTL(path.append(".mtl"));
	// if (!inMTL) {
	// 	cout << "Cannot open" << path.append(".mtl") << endl; exit(1);
	// }

	// string line1;
	// while(getline(inMTL, line1)) {
	// 	if (line.substr(0,3) == "Kd "){
	// 		istringstream s(line.substr(3));
    //         glm::vec3 d; s >> d.x; s >> d.y; s >> d.z = 1.0f;
    //         obj_dif.push_back(d);
	// 	}else if (line.substr(0,3) == "Ka ") {
    //         istringstream s(line.substr(3));
    //         glm::vec3 a; s >> a.x; s >> a.y; s >> a.z = 1.0f;
    //         obj_amb.push_back(n);
	// 	}else if (line.substr(0,3) == "Tf ") {
    //         istringstream s(line.substr(3));
    //         translucency << s;
    //         obj_normals.push_back(n);
	// 	}else if (line.substr(0,6) == "illum ") {
    //         istringstream s(line.substr(6));
    //         illumination << s;
    //         obj_normals.push_back(n);
	// 	}
	// }

	// for (int i = 0; i < numVertices; )



	// return vertex_data;
};

GLfloat*  objLoader::loadObj(std::string fileName){
	//Given "example.obj", open "GameAssets/obj/example.obj" using loadTextureFromFile;
	//Don't forget the mtl file
	return this->loadObjFromFile(fileName);
};
