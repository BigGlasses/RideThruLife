#version 330 core
 
in vec3 Color;
out vec4 outputF;
 
void main()
{
    outputF = vec4(Color,1.0);
}