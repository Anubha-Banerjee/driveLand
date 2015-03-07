/*****************************************************************************/
/* solving the first subproblem in final year BE project */
/* will output a grass-land on which a car will be movable in 3rd person view */
/*****************************************************************************/

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/glut.h>
#include "car.cpp"
#include "variables.h"
#include <stack>
#define INFINITY 1000;
using namespace std ;

GLuint test;
GLint shader;
GLuint lightposn; 
GLuint lightcolor; 
uniform colorUniform;
camera myCamera;
bool arrowKeys[4];

// create the car class object
Car mycar(0, 2, 0, 0, 0, vec3(1, 0, 0), 0);
float radius = INFINITY;
vec4 circleCenter = vec4(-radius, 0, 0, 1);



void setup()
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glDisable(GL_CULL_FACE);

	initialiseObjects();

	// intialise camera
	myCamera.eye = vec3(0,10,30);
	myCamera.up = vec3(0,1,0);
	myCamera.goal = vec3(0,10,-1);


	// Initialize shaders
	shader=gltLoadShaderPairWithAttributes("ver.vp","frag.fp",3,GLT_ATTRIBUTE_VERTEX,"vertex",GLT_ATTRIBUTE_NORMAL,"normal",GLT_ATTRIBUTE_TEXTURE0,"texture");			

	lightposn = glGetUniformLocation(shader,"lightposn") ;       
    lightcolor = glGetUniformLocation(shader,"lightcolor") ;
    colorUniform.ambientcol = glGetUniformLocation(shader,"ambient") ;       
    colorUniform.diffusecol = glGetUniformLocation(shader,"diffuse") ;       
    colorUniform.specularcol = glGetUniformLocation(shader,"specular") ;  
    colorUniform.shininesscol = glGetUniformLocation(shader,"shininess") ; 

}

// prototype for display function in display.cpp
void display(void) ;

void reshape(int width,int height){
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60,width/(float)height,0.1,1000);
	glViewport(0,0,width,height);
}

void keyPressed (unsigned char key, int x, int y)
{
	if(key == 27)
	{
		exit(0);
	}	
}

void idle()
{
	double thetaCar = 0, thetaWheel = 0;
	vec3 dir;
	float step, inc = 0.07;
	mat3 rotn, rotnCar, rotnWheel;
	mat4 transl ;
		
	step = 4 / radius;
	if(step < 0)
		step = step * -1;
	mycar.turnAngle = step;

	// left
	if(arrowKeys[0] == 1)
	{		
			rotn = Transform::rotate(mycar.wheelAngle, myCamera.up);		

			if(mycar.wheelAngle < 60)
			{
	
				mycar.wheelAngle = mycar.wheelAngle + 0.07;		
			}

			float prev_radius;
			thetaWheel =	 mycar.wheelAngle * 3.14159 / 180;	
			thetaCar =	mycar.angle * 3.141 / 180; 
			prev_radius = radius;

			// temporary hack to prevent INF
			if(mycar.wheelAngle > -0.05 && mycar.wheelAngle < 0.05)
			{
				radius = INFINITY;
			}
			else
				radius = 9 / tan(thetaWheel);			

			circleCenter.x = (prev_radius - radius) * cos(thetaCar) + circleCenter.x;
			circleCenter.z = circleCenter.z - ((prev_radius - radius) * sin(thetaCar));
					
			for(int i = 1; i <= 2; i++)
			{
				carParts[i].rotate = mat4(rotn);
				carParts[i].transform = carParts[0].transform * carParts[i].translate * carParts[i].rotate;		
			}
	}

	// up
	if(arrowKeys[1] == 1)
	{	
		/*
		dir = inc * glm::normalize(myCamera.goal - myCamera.eye);		 
        myCamera.eye = myCamera.eye + dir;
		myCamera.goal = myCamera.goal + dir;	 
		mycar.carCentre = mycar.carCentre + dir; 		*/

		cout << "radius: " << radius << " thetaWheel " << mycar.wheelAngle << "cx "<< circleCenter.x << " cz " << circleCenter.z << "\n";	

		if(mycar.wheelAngle < 0)
		{				
			mycar.angle = mycar.angle - step;
			rotn = Transform::rotate(-mycar.turnAngle, myCamera.up);	
		//	Transform::left(-mycar.turnAngle, myCamera.eye, myCamera.goal, myCamera.up, mycar.carCentre);
		}

		if(mycar.wheelAngle >= 0)
		{
			mycar.angle = mycar.angle + step;
			rotn = Transform::rotate(mycar.turnAngle, myCamera.up);
			//Transform::left(mycar.turnAngle, myCamera.eye, myCamera.goal, myCamera.up, mycar.carCentre);
		}
			
		vec4 positionNew;
		positionNew = carParts[0].position - circleCenter;
		positionNew = mat4(rotn) * positionNew;
	
		carParts[0].position = positionNew + circleCenter;

		// compute rotn of the car
		rotnCar = Transform::rotate(mycar.angle, myCamera.up);	
		rotnWheel = Transform::rotate(mycar.wheelRotnSpeed, vec3(1, 0, 0));
		mycar.wheelRotnSpeed --;
		transl = Transform::translate(carParts[0].position.x, carParts[0].position.y, carParts[0].position.z);
		
		carParts[0].transform =  transl * mat4(rotnCar);	

		// transform the wheels
		carParts[1].transform =  carParts[0].transform * carParts[1].translate * carParts[1].rotate * mat4(rotnWheel);
		carParts[2].transform = carParts[0].transform * carParts[2].translate * carParts[2].rotate  * mat4(rotnWheel) ;
		carParts[3].transform = carParts[0].transform * carParts[3].translate * mat4(rotnWheel);	
		carParts[4].transform = carParts[0].transform * carParts[4].translate * mat4(rotnWheel);	
	}

	// right
	if(arrowKeys[2] == 1)
	{		
			rotn = Transform::rotate(mycar.wheelAngle, myCamera.up);

			if(mycar.wheelAngle > -60)
			{
				mycar.wheelAngle = mycar.wheelAngle - 0.07;
			}
			
			float prev_radius;
			thetaWheel =	 mycar.wheelAngle * 3.14159 / 180;			
			thetaCar =	mycar.angle * 3.141 / 180; 
			prev_radius = radius;

			// temporary hack to prevent INF
			if(mycar.wheelAngle > -0.05 && mycar.wheelAngle < 0.05)
			{
				radius = INFINITY;
			}
			else
				radius = 9 / tan(thetaWheel);
	
			circleCenter.x = (prev_radius - radius) * cos(thetaCar) + circleCenter.x;
			circleCenter.z = circleCenter.z - ((prev_radius - radius) * sin(thetaCar));
					
			for(int i = 1; i <= 2; i++)
			{
				carParts[i].rotate = mat4(rotn);
				carParts[i].transform = carParts[0].transform * carParts[i].translate * carParts[i].rotate;		
			}		
	}	
}

void specialUp(int key, int x, int y) {
	switch(key) {
	case 100: //left
		arrowKeys[0] = 0;
		break;
	case 101: //up
		arrowKeys[1] = 0;		
		break;
	case 102: //right
		arrowKeys[2] = 0;
        break;
	case 103: //down	
		arrowKeys[3] = 0;
        break;
	}	
}


void specialDown(int key, int x, int y) {	

	switch(key) {
	case 100: //left
		arrowKeys[0] = 1;
		break;
	case 101: //up
		arrowKeys[1] = 1;		
		break;
	case 102: //right
		arrowKeys[2] = 1;
        break;
	case 103: //down	
		arrowKeys[3] = 1;
        break;
	}	
	
}

void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowPosition(0,0);


	glutCreateWindow("driveLand");	
	glutFullScreen();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(specialDown);
    glutSpecialUpFunc(specialUp);
	glutIdleFunc(idle);

	glewInit();

	setup();
	glutMainLoop();

}