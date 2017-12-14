#version 330 core

// Input vertex data, different for all executions of this shader.
layout (location=0) in vec3 position;
layout (location=1) in vec3 color;
layout (location=2) in vec2 textureCoord;
layout (location=3) in vec3 normalV;
layout (location=4) in float shinyV;
layout (location=5) in vec3 specularV;



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
out vec2 texCoord;
out vec3 normal;
out vec3 specular;
out vec3 pos;
out float shiny;

void main(){
	Color = color;
 	ShadowCoord = biasMatrix * pLightMatrix * mvLightMatrix * vec4(position, 1);
    gl_Position = vec4( pMatrix * mvMatrix * vec4(position, 1));
    pos = vec3(gl_Position);
    texCoord = textureCoord;
    normal = normalV;

    specular = specularV;
    shiny = shinyV;
}