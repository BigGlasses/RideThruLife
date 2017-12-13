#version 330 core

uniform sampler2D normalTexture;
uniform sampler2D shadowTexture;
in vec3 Color;
in vec4 ShadowCoord;
in vec2 texCoord;
out vec4 outputF;
 
void main()
{
	float bias = 0.005;
	float visibility = 1.0;
	if ( texture( shadowTexture, ShadowCoord.xy ).z  <  ShadowCoord.z-bias){
	    visibility = 0.5;
	}
    outputF = vec4(Color * texture(normalTexture, texCoord).rgb *visibility,1.0);
}