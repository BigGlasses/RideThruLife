#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>
#include "OpenGLImports.hpp"
#include "basicShapes.hpp"
#include "shaderLoader.hpp"
#include "textureLoader.hpp"
#include "objLoader.hpp"
#include "GameModel.hpp"
#include "camera.hpp"


//Constants
const int RENDERMODE_SOLID = 0;
const int RENDERMODE_WIREFRAME = 1;
const int RENDERMODE_SOLIDWIREFAME = 2;
float camPos[] = {0, 0, 3.42f};	//where the camera is
float lightPos[] = {5, 5, 5};


//Window size
int WINDOWX = 800;
int WINDOWY = 800;


//State variables
float yaw = 0;
float pitch = 0;
float timePassed;
int FPS = 60;

GLuint screenTexture;
GLuint screenDepthTexture;
GLuint screenFBO;

GLuint shadowTexture;
GLuint shadowFBO;

GLuint shaderProgram1;
GLuint shaderProgram2;

GLuint mvMatrixLoc;
GLuint pMatrixLoc;
GLuint mvMatrixShadowLoc;
GLuint pMatrixShadowLoc;
GLuint mvMatrixLightLoc;
GLuint pMatrixLightLoc;

GLuint normalTexLoc;
GLuint shadowTexLoc;

GLuint timeLoc;
GLfloat  modelViewMatrix[16]; 
GLfloat  projectionMatrix[16]; 
GLfloat  modelViewLightMatrix[16]; 
GLfloat  projectionLightMatrix[16]; 
GLfloat  biasMatrix[16] = {
0.5, 0.0, 0.0, 0.0,
0.0, 0.5, 0.0, 0.0,
0.0, 0.0, 0.5, 0.0,
0.5, 0.5, 0.5, 1.0}
; 


shaderLoader shaderLoading;
textureLoader textureLoading;
objLoader objLoading;
Camera cam;

GLuint kek; 
std::string title = "example2";
GameModel *gm;
//GameModel *gm;

// Updates the camera position to reflect the yaw, pitch.
void updateCamera(){
	camPos[0] = 8.0 * cos(yaw);
	camPos[1] = 8.0 * sin(yaw);
	camPos[2] = 0.5 * 4.0 * sin(pitch);
}


void prepareScreen(){
	glBindTexture(GL_TEXTURE_2D, 0);
	glGenTextures(1, &screenTexture);
	glBindTexture(GL_TEXTURE_2D, screenTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOWX, WINDOWY,0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);
	glGenTextures(1, &screenDepthTexture);
	glBindTexture(GL_TEXTURE_2D, screenDepthTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, WINDOWX, WINDOWY,0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &screenFBO);

	glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, screenDepthTexture, 0);

	 if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){  //Check for FBO completeness
	 	printf( "Error! Screen FrameBuffer is not complete");
	 }

	 glBindFramebuffer(GL_FRAMEBUFFER, 0);
	 
	}

//Prepares the shadow FBO
	void prepareShadow(){
		glGenFramebuffers(1, &shadowFBO);

		glBindTexture(GL_TEXTURE_2D, 0);
		glGenTextures(1, &shadowTexture);

		glBindTexture(GL_TEXTURE_2D, shadowTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, WINDOWX, WINDOWY, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowTexture, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	 if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){  //Check for FBO completeness
	 	printf( "Error! Shadow FrameBuffer is not complete");
	 }
	 glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

//Prepares the shader.
	void prepareShaders(){
		shaderProgram1 = glCreateProgram();
		GLuint vertexShader = shaderLoading.loadShaderFromFile( "shaders/testshader.vert", GL_VERTEX_SHADER );
		glAttachShader( shaderProgram1, vertexShader );
		GLuint fragmentShader = shaderLoading.loadShaderFromFile( "shaders/testshader.frag", GL_FRAGMENT_SHADER );
		glAttachShader( shaderProgram1, fragmentShader );
		glLinkProgram( shaderProgram1 );

		shaderProgram2 = glCreateProgram();
		vertexShader = shaderLoading.loadShaderFromFile( "shaders/shadowShader.vert", GL_VERTEX_SHADER );
		glAttachShader( shaderProgram2, vertexShader );
		fragmentShader = shaderLoading.loadShaderFromFile( "shaders/shadowShader.frag", GL_FRAGMENT_SHADER );
		glAttachShader( shaderProgram2, fragmentShader );
		glLinkProgram( shaderProgram2 );



    //Get uniforms
		mvMatrixLoc = glGetUniformLocation(shaderProgram1, "mvMatrix");
		pMatrixLoc = glGetUniformLocation(shaderProgram1, "pMatrix");
		timeLoc = glGetUniformLocation(shaderProgram1, "time");
		mvMatrixShadowLoc = glGetUniformLocation(shaderProgram2, "mvMatrix");
		pMatrixShadowLoc = glGetUniformLocation(shaderProgram2, "pMatrix");
		mvMatrixLightLoc = glGetUniformLocation(shaderProgram2, "mvLightMatrix");
		pMatrixLightLoc = glGetUniformLocation(shaderProgram2, "pLightMatrix");
		normalTexLoc = glGetUniformLocation(shaderProgram2, "normalTexture");
		shadowTexLoc = glGetUniformLocation(shaderProgram2, "shadowTexture");

	}


//GLUT keyboard functions
	void keyboard(unsigned char key, int xIn, int yIn)
	{
		// cam.keyPressed(key);
		switch (key)
		{
			case 'q':
			case 27:	//27 is the esc key
			exit(0);
			break;
			case 'd':
			break;
			case 'j':
			yaw += 0.1;
			break;
			case 'l':
			yaw -= 0.1;
			break;
			case 'i':
			pitch += 0.1;
			break;
			case 'k':
			pitch -= 0.1;
			break;
	}
}

void mouseMove(int x, int y){
	//cam.mouseMove( x, y, WINDOWX, WINDOWY);
}
void mousePressed(int btn, int state, int x, int y){
	//cam.mousePressed(btn, state, x, y);
}

void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
	glViewport(0, 0, WINDOWX, WINDOWY);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	kek = textureLoading.loadTexture("example.bmp");
	gm  = new GameModel(title);
}

//Prepares the display
void prepareDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	prepareScreen();
	prepareShadow();
	prepareShaders();
	prepareBuffers();
}

//Updates the modelview and projection matrix variables.
void updateShadowMatrices(){
	glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);  
	glUniformMatrix4fv(mvMatrixShadowLoc,  1, GL_FALSE, modelViewMatrix);
	glUniformMatrix4fv(pMatrixShadowLoc,  1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(mvMatrixLightLoc,  1, GL_FALSE, modelViewLightMatrix);
	glUniformMatrix4fv(pMatrixLightLoc,  1, GL_FALSE, projectionLightMatrix);
	glUniform1f(timeLoc, timePassed);
	glUniform1i(normalTexLoc, 0);
	glUniform1i(shadowTexLoc, 1);
}

//Updates the modelview and projection matrix variables.
void updateLightMatrices(){
	glGetFloatv(GL_PROJECTION_MATRIX, projectionLightMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelViewLightMatrix);  
	glUniformMatrix4fv(mvMatrixLoc,  1, GL_FALSE, modelViewLightMatrix);
	glUniformMatrix4fv(pMatrixLoc,  1, GL_FALSE, projectionLightMatrix);
	glUniform1f(timeLoc, timePassed);
}

//Renders the scene
void renderScene(void){

}


void display(void)
{
	//flush out to single buffer
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	
	glDisable(GL_TEXTURE);
	//First Pass (shadows)
	glClearColor(0, 0, 0, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glClear( GL_DEPTH_BUFFER_BIT );
	glOrtho(-10, 10, -10, 10, 1, 40);
	gluLookAt(lightPos[0], lightPos[1], lightPos[2], 0, 0, 0, 0, 0, 1);
	glUseProgram(shaderProgram1);
	
	updateLightMatrices();
	gm->draw();
	glTranslatef(0, 0, 1);
	glScalef(2, 2, 0.1);
	updateLightMatrices();
	gm->draw();


	//Retain the basic light transformations, for the shadow pass
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, 1, 40);
	gluLookAt(lightPos[0], lightPos[1], lightPos[2], 0, 0, 0, 0, 0, 1);
	updateLightMatrices();
	
	glUseProgram(0);
	//renderScene();// First Pass


	//Second pass
	updateCamera();
	glLoadIdentity();
	glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);
	glEnable(GL_TEXTURE);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, shadowTexture);

	glActiveTexture(GL_TEXTURE0);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluPerspective(90, float(WINDOWX)/WINDOWY, 1, 40);
	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0, 0, 1);
	//cam.updateView();

	//glLoadMatrixf(vm);
	glUseProgram(shaderProgram2);

	updateShadowMatrices();
	gm->draw();
	glTranslatef(0, 0, 1);
	glScalef(2, 2, 0.1);
	updateShadowMatrices();
	gm->draw();
	
	glUseProgram(0);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);

	glBindTexture(GL_TEXTURE_2D, screenTexture);
	//glBindTexture(GL_TEXTURE_2D, kek);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glColor3f(1, 1, 1);

	glBegin(GL_QUADS);

	glVertex3f(-1, -1, 0);
	glTexCoord2f(0, 1); 

	glVertex3f(-1,  1, 0);
	glTexCoord2f(1, 1); 

	glVertex3f( 1,  1, 0);
	glTexCoord2f(1, 0); 

	glVertex3f( 1, -1, 0);
	glTexCoord2f(0, 0); 

	glEnd();

	glDisable(GL_TEXTURE_2D);
	//renderScene();
	glBindTexture(GL_TEXTURE_2D, 0);
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void tickTime(){
	timePassed += 1/((float)FPS);
	while ( timePassed > 1 ) timePassed -= 1;
}

void FPSUpdate(int i){
	glutTimerFunc(1000/FPS, FPSUpdate , 0);
	glutPostRedisplay();
	tickTime();
}


void resizeFunc(int x, int y){
	glutReshapeWindow( WINDOWX, WINDOWY);
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WINDOWX, WINDOWY);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("RideThruLife v0");	//creates the windowx

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
	  /* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));



	prepareDisplay();
	//createMenu();

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mousePressed);
	glutPassiveMotionFunc(mouseMove);
	//glutSpecialFunc(SpecialInput);
	glutTimerFunc(1000/FPS, FPSUpdate , 0);
	glutReshapeFunc(resizeFunc);
	init();

	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,0);


	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
