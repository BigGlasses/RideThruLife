#version 330 compatibility

uniform mat4 mvMatrix, pMatrix;
uniform float time;

layout (location=0) in vec3 position;
layout (location=1) in vec3 color;
layout (location=2) in vec2 textureCoord;
layout (location=3) in vec3 normal;
layout (location=4) in float shiny;
layout (location=5) in vec3 specular;
//layout (location=0) in vec3 normals;
float pi = 3.1415926535897932384626433832795;
out vec3 Color;
 
void main()
{
	Color = color;// * (0.7 + sin(time*position.x * pi*2)/6 + cos(time*position.y * pi*2)/6);
    gl_Position = pMatrix * mvMatrix * vec4(position, 1);
    //gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 1); //Deprecated way to transform 3D to 2D
}