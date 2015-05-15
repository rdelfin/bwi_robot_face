#include <ros/ros.h>
#include "face_detection/eye.h"
#include "face_detection/face.h"
#include "face_detection/faceDetection.h"

#include <GL/glut.h>

#include <iostream>
#include <stdio.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>  

using namespace std;

//Variables change when window is created, resized
int windowWidth;
int windowHeight;

int windowX;
int windowY;

float robotLeftEyeX = -0.82f;
float robotLeftEyeY = 0.48f;

float robotRightEyeX = 0.18f;
float robotRightEyeY = 0.48f;

float robotEyeWidth = 0.64f;
float robotEyeHeight = 0.48f;

float robotPupilWidth = 0.1f;
float robotPupilHeight = 0.1f;

//robotPupil coordinates are based off of eye coordinates
float robotPupilX = 0.27f;
float robotPupilY = 0.19f;

//Camera input dimensions
int frameWidth;
int frameHeight;

bool pushedBack = false;

face_detection::faceDetection inputFaces;

void changePupil();
void changeDimensions();
void renderScene(void);

void detectedFacesCallback(const face_detection::faceDetection::ConstPtr& faceDetect){
  ROS_INFO("I read in [%i] faces\n", faceDetect->faceCount);

  frameWidth = faceDetect->frameWidth;
  frameHeight = faceDetect->frameHeight;
  inputFaces.faceCount = faceDetect->faceCount;
  inputFaces.faces = faceDetect->faces;
  
  changePupil();
  
  //changePupilPos();
  renderScene();
  //changePupilpos(faceDetect);
}

void changePupil()
{
  //pupil size will be based on the size of the detected face, relative
  //to the size of the capture frame.

  //if no faces, reset
  if(inputFaces.faceCount == 0)
    {
      //robotPupilWidth = 0.5f;
      //robotPupilHeight = 0.5f;
      //robotPupilX = 0.27f;
      //robotPupilY = 0.19f;
    }
  else
    {
      //We have to flip the coordinates given in inputFaces, face_detection_node
      //gives mirrored coordinates.

      //Converting pixel width to the openGL -1 to 1 format
      //
      
      //***TODO***
      //Handling cameras of different ratios
      //**********

      
      
      //robotPupilWidth = (float) inputFaces.faces[0].width / 1000;
      //ROS_INFO("robotPupilWidth [%f]", robotPupilWidth);
      //robotPupilHeight = (float) inputFaces.faces[0].height / 1000;
      //ROS_INFO("robotPupilHeight [%f]", robotPupilHeight);

      float temp = ((frameWidth - inputFaces.faces[0].x));
      temp /=1000;
      temp -= robotPupilWidth;

      //ROS_INFO("Putting [%f] in robotPupilX", temp);
      robotPupilX = (float) temp;

      temp = ((frameHeight - inputFaces.faces[0].y));
      temp /=1000;
      temp -= robotPupilHeight;
      
      //ROS_INFO("Putting [%f] in robotPupilY", temp);
      robotPupilY = (float) temp;
      
    }
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

float angle = 0.0f;

void renderLeftEye(void)
{
  glBegin(GL_QUADS);

  //Set color to white
  glColor3f(1.0f, 1.0f, 1.0f);
  
  glVertex3f(robotLeftEyeX, robotLeftEyeY, -0.1f);
  glVertex3f((robotLeftEyeX + robotEyeWidth),robotLeftEyeY, -0.1f);
  glVertex3f((robotLeftEyeX + robotEyeWidth), (robotLeftEyeY - robotEyeHeight), -0.1f);
  glVertex3f(robotLeftEyeX, (robotLeftEyeY - robotEyeHeight), -0.1f);

  glEnd();
}

void renderRightEye(void)
{
  glBegin(GL_QUADS);

  //Set color to white
  glColor3f(1.0f, 1.0f, 1.0f);
  
  glVertex2f(robotRightEyeX, robotRightEyeY);
  glVertex2f((robotRightEyeX + robotEyeWidth),robotRightEyeY);
  glVertex2f((robotRightEyeX + robotEyeWidth), (robotRightEyeY - robotEyeHeight));
  glVertex2f(robotRightEyeX, (robotRightEyeY - robotEyeHeight));

  glEnd();
}

void renderLeftPupil(void)
{
  glBegin(GL_QUADS);

  //Set color to black
  glColor3f(0.0f, 0.0f, 0.0f);

  //Top Right 
  glVertex2f((robotLeftEyeX + robotPupilX + robotPupilWidth), (robotPupilY + robotPupilHeight));
  
  //Top Left
  glVertex2f((robotLeftEyeX + robotPupilX), (robotPupilY + robotPupilHeight));
  //Bottom Left
  glVertex2f((robotLeftEyeX + robotPupilX), (robotPupilY));
  
  //Bottom Right
  glVertex2f((robotLeftEyeX + robotPupilX + robotPupilWidth), (robotPupilY));
 
  

  glEnd();

}

void renderRightPupil(void)
{
  glBegin(GL_QUADS);

  //Set color to black
  glColor3f(0.0f, 0.0f, 0.0f);

  //Top Right 
  glVertex2f((robotRightEyeX + robotPupilX + robotPupilWidth), (robotPupilY + robotPupilHeight));
  
  //Top Left
  glVertex2f((robotRightEyeX + robotPupilX), (robotPupilY + robotPupilHeight));
  //Bottom Left
  glVertex2f((robotRightEyeX + robotPupilX), (robotPupilY));
  
  //Bottom Right
  glVertex2f((robotRightEyeX + robotPupilX + robotPupilWidth), (robotPupilY));
 
  

  glEnd();
  
}

void renderScene(void) {

  ROS_INFO("renderScene called");

  //Clear color, aka background color. Set to black
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);  
  glClear(GL_COLOR_BUFFER_BIT);

  
  //glTranslatef(0.0f, 0.0f, -0.5f);
  
  renderLeftEye();
  renderRightEye();
  renderLeftPupil();
  renderRightPupil();
  

  //glutSwapBuffers();
  glFlush();
  
}

void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
 
   // Draw a Red 1x1 Square centered at origin
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 1.0f, 0.0f); // Red
      glVertex2f(-0.5f, -0.5f);    // x, y
      glVertex2f( 0.5f, -0.5f);
      glVertex2f( 0.5f,  0.5f);
      glVertex2f(-0.5f,  0.5f);
   glEnd();
 
   glFlush();  // Render now
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "robot_face_node");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/detectedFaces",1000,detectedFacesCallback);
  
  // init GLUT and create window
  /*
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(600,600);
	glutCreateWindow("robot_face_node");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(ros::spinOnce);
	//glutIdleFunc(renderScene);
	// enter GLUT event processing cycle
	*/

   glutInit(&argc, argv);                 // Initialize GLUT
   glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   glutInitWindowSize(600, 400);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutDisplayFunc(renderScene); // Register display callback handler for window re-paint

   glutIdleFunc(ros::spinOnce);
	glutMainLoop();
}
