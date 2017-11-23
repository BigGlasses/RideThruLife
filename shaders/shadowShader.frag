#version 330 core

uniform sampler2D shadowMap;
in vec3 Color;
in vec4 ShadowCoord;
out vec4 outputF;
 
void main()
{
	float bias = 0.005;
	float visibility = 1.0;
	if ( texture( shadowMap, ShadowCoord.xy ).z  <  ShadowCoord.z-bias){
	    visibility = 0.5;
	}
    outputF = vec4(Color*visibility,1.0);
}