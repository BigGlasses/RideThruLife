#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "OpenGLImports.hpp"
#include "GameData.hpp"
#include "shaderLoader.hpp"
#include "textureLoader.hpp"
#include "objLoader.hpp"
#include "GameModel.hpp"
#include "camera.hpp"
#include "vehicleselect.hpp"
#include "vehicle.hpp"
#include "collectible.hpp"

#define PI 3.14159265

//Constants
const int GAMESTATE_VEHICLESELECT = 0;
const int GAMESTATE_START_GAME = 1;
const int GAMESTATE_STARTED_GAME = 2;
int gamestate = GAMESTATE_VEHICLESELECT;


//State variables
float yaw = 0;
float pitch = 0;

GLuint screenTexture;
GLuint screenDepthTexture;
GLuint screenFBO;

GLuint shadowTexture;
GLuint shadowFBO;


// GLfloat  biasMatrix[16] = {
// 0.5, 0.0, 0.0, 0.0,
// 0.0, 0.5, 0.0, 0.0,
// 0.0, 0.0, 0.5, 0.0,
// 0.5, 0.5, 0.5, 1.0}
// ;


textureLoader textureLoading;
objLoader objLoading;
Camera cam;
VehicleSelect vs;
Vehicle vehicle;
GameModel levelplain;
float life = 100;
int maxLife = 100;

std::vector<Collectible> clist;


bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)

void keyPressed (unsigned char key, int x, int y) {
		vs.keyboard(key, x, y);
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
			vehicle.jump();
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

	keyStates[key] = true; // Set the state of the current key to pressed
}

void keyUp (unsigned char key, int x, int y) {
keyStates[key] = false; // Set the state of the current key to not pressed
}

// Updates the camera position to reflect the yaw, pitch.
void updateCamera(){
	camPos[0] = vehicle.getTrailX(20) - 10 * sin(vehicle.getRotation()* PI / 180.0 ) * vehicle.getScale();
	camPos[1] = vehicle.getTrailY(20) + 10  * vehicle.getScale();
	camPos[2] = vehicle.getTrailZ(20) - 10	 * cos(vehicle.getRotation()* PI / 180.0 )  * vehicle.getScale();

	lightPos[0] = 50;
	lightPos[1] = 50;
	lightPos[2] = 50;

	camDir[0] = - camPos[0] + 16.0 * cos(yaw);
	camDir[1] = - camPos[1] + 16.0 * sin(pitch);
	camDir[2] = - camPos[2] + 16.0 * sin(yaw);
}

void addCollectible(){

	float x0 = -400 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(400- -400)));
	float y0 = 0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(20 - 0)));
	float z0 = -400 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(400- -400)));
	clist.push_back(Collectible(x0, y0, z0, FPS*10, gms[11]));
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
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




void keyOperations (void) {
	if (GAMESTATE_STARTED_GAME){
		if (keyStates['w'])
			vehicle.accelerate(true);
		else vehicle.accelerate (false);

		if (keyStates['s'])
				vehicle.brake(true);
		else vehicle.brake (false);

		vehicle.shouldTurn(true);
		if (keyStates['a'])
			vehicle.turn(true);
		else if (keyStates['d'])
			vehicle.turn(false);
		else vehicle.shouldTurn(false);
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
	loadAssets();
	vs.init();
	levelplain = GameModel(std::string("level"));


}

//Prepares the display
void prepareDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	prepareScreen();
	prepareShadow();
	prepareShaders();
}

//Renders the scene
void renderScene(void){

}

void lightProject(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 50, -50, 50, -10, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(lightPos[0] + vehicle.getX(), lightPos[1] + vehicle.getY(), lightPos[2] + vehicle.getZ(), vehicle.getX(), vehicle.getY(), vehicle.getZ(), 0, 1, 0);
	focusOnLights();
	updateMatrices();
}

void cameraProject(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, float(WINDOWX)/WINDOWY, 1, 2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camPos[0], camPos[1], camPos[2], vehicle.getX(), vehicle.getY(), vehicle.getZ(), 0, 1, 0);
	focusOnShadows();
	updateMatrices();
}

void display(void)
{
	//flush out to single buffer
	if (gamestate == GAMESTATE_VEHICLESELECT){
		vs.draw();
		vs.update();
	}
	else{

	lightProject();
	glEnable(GL_DEPTH_TEST);

	focusOnLights();
	//First Pass (shadows)
	glClearColor(0, 0, 0, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glClear( GL_DEPTH_BUFFER_BIT );
	glUseProgram(shaderProgram1);
	cameraProject();
	updateMatrices();
	updateMatrices();
	levelplain.draw();
	updateMatrices();
	gms[3].draw();	
	for (int i; i <3; i ++){
		clist[i].draw(true);
	}
	vehicle.draw(true);


	//Retain the basic light transformations, for the shadow pass
	lightProject();
	updateMatrices();

	glUseProgram(0);
	//renderScene();// First Pass

	//Second pass
	glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, shadowTexture);

	glActiveTexture(GL_TEXTURE0);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//cam.updateView();


	glUseProgram(shaderProgram2);

	lightProject();
	cameraProject();
	levelplain.draw();
	gms[3].draw();
	for (int i = 0; i < life; i ++){

		lightProject();
		glTranslatef(vehicle.getTrailX(i), vehicle.getTrailY(i), vehicle.getTrailZ(i));
		glScalef(2, 2, 2);
		updateMatrices();

		cameraProject();
		glTranslatef(vehicle.getTrailX(i), vehicle.getTrailY(i), vehicle.getTrailZ(i));
		glScalef(2, 2, 2);
		updateMatrices();
		gms[11].draw();
	}

	for (int i = 0; i <3; i ++){
		lightProject();
		clist[i].draw(false);
		cameraProject();
		clist[i].draw(true);
	}

	lightProject();
	vehicle.draw(false);

	cameraProject();
	vehicle.draw(true);

	glUseProgram(0);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, screenTexture);
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
	}
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gameLoop(){
	keyOperations();
	vehicle.update();
	updateCamera();
	for (int i = 0; i <3; i ++){
		clist[i].update();
		if (clist[i].canBeCollected(vehicle.getX(), vehicle.getY(), vehicle.getZ())){
			clist.erase(clist.begin() + i);
			addCollectible();
			life = maxLife;
		}
	}
	life -= 0.1;
	if (life < 0) {
		vs.boot();
		gamestate =GAMESTATE_VEHICLESELECT;
	}

}

void FPSUpdate(int i){
	glutTimerFunc(1000/FPS, FPSUpdate , 0);
	vs.update();

	if (gamestate == GAMESTATE_VEHICLESELECT && vs.selected()){
		gamestate = GAMESTATE_STARTED_GAME;
		addCollectible();
		addCollectible();
		addCollectible();
		life = maxLife;
		std::string vname = vs.selectedVehicleName();
		GameModel m = GameModel(vname);
		if (vname == "car"){
			vehicle = Vehicle(0, 0, 0, 1.0, 2.0, 1.0, 1.0, 1.0, false, m);
		}
		else if (vname == "dinner_table"){
			vehicle = Vehicle(0, 0, 0, 0.7, 1.2, 0.3, 1.0, 1.0, false, m);
		}
		else if (vname == "christmas_tree"){
			vehicle = Vehicle(0, 0, 0, 2.0, 5.0, 4.0, 2.0, 1.0, false, m);
		}
		else if (vname == "grill"){
			vehicle = Vehicle(0, 0, 0, 1.2, 1.6, 0.8, 1.2, 1.0, false, m);
		}
		else if (vname == "bike"){
			vehicle = Vehicle(0, 0, 0, 1.5, 1.8, 0.7, 1.0, 1.0, false, m);
		}
		else if (vname == "balloon"){
			vehicle = Vehicle(0, 0, 2.5, 3.0, 2.5, 0.3, 1.6, 1.0, false, m);
		}
		else if (vname == "hot_air_balloon"){
			vehicle = Vehicle(0, 0, 4.5, 0.2, 0.3, 0.2, 0.7, 1.0, false, m);
		}
		else if (vname == "claw"){
			vehicle = Vehicle(0, 0, 0, 0.5, 0.5, 0.7, 0.5, 1.0, false, m);
		}
		else if (vname == "row_boat"){
			vehicle = Vehicle(0, 0, 0, 0.8, 1.4, 0.8, 1.3, 1.0, true, m);
		}
		else if (vname == "building"){
			vehicle = Vehicle(0, 0, 0, 1.5, 0.5, 0.7, 1.5, 3.0, false, m);
		}
		else if (vname == "snowman"){
			vehicle = Vehicle(0, 0, 0, 2.5, 1.5, 0.7, 1.5, 1.0, false, m);
		}
		else if (vname == "barrel"){
			vehicle = Vehicle(0, 0, 0, 1.5, 0.5, 1.7, 3.5, 1.0, false, m);
		}
	}
	if (gamestate == GAMESTATE_STARTED_GAME){
		gameLoop();
	}
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

	glutCreateWindow("RideThruLife v1");	//creates the windowx

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
	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events
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
