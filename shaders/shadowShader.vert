#version 330 core

// Input vertex data, different for all executions of this shader.
layout (location=0) in vec3 position;
layout (location=1) in vec3 color;

// Values that stay constant for the whole mesh.
uniform mat4 mvMatrix, pMatrix;
uniform mat4 mvLightMatrix, pLightMatrix;
mat4 biasMatrix = mat4(
0.5, 0.0, 0.0, 0.0,
0.0, 0.5, 0.0, 0.0,
0.0, 0.0, 0.5, 0.0,
0.5, 0.5, 0.5, 1.0);

out vec4 ShadowCoord;
out vec3 Color;

void main(){
	Color = color;
 	ShadowCoord = biasMatrix * pLightMatrix * mvLightMatrix * vec4(position, 1);
    gl_Position = pMatrix * mvMatrix * vec4(position, 1);
}