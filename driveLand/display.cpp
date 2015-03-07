#include <GL/glew.h>
#include <GL/glut.h>
#include "variables.h"
#include<iostream>

using namespace std;



void transformvec (const GLfloat input[4], GLfloat output[4]) 
{
    GLfloat modelview[16]; // in column major order
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview); 

    for (int i = 0 ; i < 4 ; i++) {
        output[i] = 0; 
        for (int j = 0 ; j < 4 ; j++) {
            output[i] += modelview[4*j+i] * input[j]; 
        }
    }
}


void display() 
{
	glClearColor(0, 0.4, 0.6, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		

	
	
	glMatrixMode(GL_MODELVIEW);
	mat4 mv, transform(1.0);	
	mv = glm::lookAt(myCamera.eye, myCamera.goal, myCamera.up); 		

	glLoadMatrixf(&mv[0][0]); 
	
	glUseProgram(shader);
	
	const GLfloat light_positional[] = {0, 200, -250, 1}; 
	const GLfloat color[] =  {0.6,0.3,0,1};   

	GLfloat light[4] ;
	transformvec(light_positional, light) ;
	
	// setting light position and color
	glUniform4fv(lightposn, 1, light) ; 	
	glUniform4fv(lightcolor,1,color);

	for(int i = 0; i < 1; i++)
	{ 		
		transform = mv * objects[i].transform;
		glLoadMatrixf(&transform[0][0]);
		glUniform4fv(colorUniform.ambientcol,1,objects[i].ambient) ; 
		glUniform4fv(colorUniform.diffusecol,1,objects[i].diffuse) ; 
		glUniform4fv(colorUniform.specularcol,1,objects[i].specular) ; 
		glUniform1fv(colorUniform.shininesscol,1,&objects[i].shininess) ;		
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );	
		glBindTexture(GL_TEXTURE_2D,objects[i].texture);	
		objects[i].batch.Draw();		
	}

	for(int i = 0; i < 6; i++)
	{ 		

		// temp hack to bundle up car trans's in pne
		if(i == 5)
		{
			carParts[i].transform = carParts[0].transform;
		}
		transform = mv * carParts[i].transform;
		glLoadMatrixf(&transform[0][0]);
		glUniform4fv(colorUniform.ambientcol,1,carParts[i].ambient) ; 
		glUniform4fv(colorUniform.diffusecol,1,carParts[i].diffuse) ; 
		glUniform4fv(colorUniform.specularcol,1,carParts[i].specular) ; 
		glUniform1fv(colorUniform.shininesscol,1,&carParts[i].shininess) ;		
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );	
		glBindTexture(GL_TEXTURE_2D, carParts[i].texture);	
		carParts[i].batch.Draw();		
	}

	//glutSolidTeapot(5);
	glutSwapBuffers();
	glutPostRedisplay();
}
