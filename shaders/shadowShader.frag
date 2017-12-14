#version 330 core

uniform sampler2D normalTexture;
uniform sampler2D shadowTexture;
uniform vec3 camDir;

in vec3 Color;
in vec4 ShadowCoord;
in vec2 texCoord;
in vec3 normal;
in vec3 specular;
in vec3 pos;
in float shiny;
out vec4 outputF;
 
void main()
{
	float bias = 0.005;
	float visibility = 1.0;
    vec3 lightPosition = vec3(5, 5, 5);
	if ( texture( shadowTexture, ShadowCoord.xy ).z  <  ShadowCoord.z-bias){
	    visibility = 0.5;
	}

	vec3 L = normalize(lightPosition - pos);   
   	vec3 E = normalize(-pos); // we are in Eye Coordinates, so EyePos is (0,0,0)  
   	vec3 R = normalize(-reflect(L,normal));  
 
   //calculate Ambient Term:  
   vec3 Iamb = vec3(0.25, 0.25, 0);

   //calculate Diffuse Term:  
   vec3 Idiff = Color * texture(normalTexture, texCoord).rgb * max(dot(normal,L), 0.0);
   Idiff = clamp(Idiff, 0.0, 1.0);
   
   // calculate Specular Term:
   vec3 Ispec = specular * pow(max(dot(R,E),0.0),0.3*shiny);
   Ispec = clamp(Ispec, 0.0, 1.0);

   // write Total Color:  
   outputF = vec4( (Iamb + Idiff + Ispec * 0.25) * visibility, 1.0);



 //    outputF = vec4(Color * texture(normalTexture, texCoord).rgb,1.0);
 //    float lightPower =  clamp( dot( normal, vec3(1, 0, 1) ), 0,1 );

	// vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * outputF.rgb;

 //    vec3 R = reflect(-lightPosition,normal);
    
 //    float cosAlpha = clamp( dot( normalize(camDir),R ), 0,1 );

 //    float cosBeta = clamp( dot( normalize(camDir),R ), 0,1 );


 //    vec3 diffuse = vec3(outputF);

 //    outputF = vec4 (MaterialAmbientColor + diffuse * cosAlpha +  specular * pow(cosAlpha,shiny) *, outputF.a) * visibility * lightPower;
    //outputF = vec4 (normal, 1.0);
            

}