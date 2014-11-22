//
//  main.cpp
//  SolarSystem
//
//  Created by John Petersson on 2014-11-21.
//  Copyright (c) 2014 John Petersson. All rights reserved.
//
#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__
#include <GL/freeglut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

//#include <OpenGL/glfw.h>

#else
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

static GLfloat spin = 0.0;

void display(void){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.7, 0.1, 0.1);
    
    glEnable(GL_DEPTH_TEST);							// enable Z-buffering
    
    int w = glutGet((GLenum)GLUT_WINDOW_WIDTH);
    int h = glutGet((GLenum)GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, w, h);								// Set viewport
    
    glBegin(GL_POLYGON);
        glVertex3f (-10.25, -10.25, 1.0);
        glVertex3f (10.75, -10.25, -2.0);
        glVertex3f (10.75, 10.75, -2.0);
        glVertex3f (-10.25, 10.75, 1.0);
    glEnd();
    
    glColor3f(0.7, 0.1, 1);
    glutWireSphere(10, 100, 6);
    
    glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(50, 4, 4);
    glPopMatrix();
    
    glutSolidSphere(30, 100, 10);
    
    glutSwapBuffers();
    

    //glFlush();
}

void spinDisplay(void)
{
    spin += 1.0;
    if (spin > 360.0)
        spin = spin - 360.0;
    glutPostRedisplay();
}

void initGL() {
    
    glClearColor(0.0,0.0,0.0,0.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    
}

void mouse(int button, int state, int x, int y) {
    
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                glutIdleFunc(spinDisplay);
                break;
            } else {
                glutIdleFunc(NULL);
                break;
            }

            case GLUT_RIGHT_BUTTON:
                if (state == GLUT_DOWN) {
                    glutIdleFunc(NULL);
                }
                break;
            default: break;
    }
}

void handleKeys(unsigned char key, int /*x*/, int /*y*/)
{
    switch( key )
    {
            // Key 27 => Escape.
        case 27:
        {
            exit( 0 );
            break;
        }
    }
}

void handleSpecialKeys(int key, int /*x*/, int /*y*/)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            printf("Left arrow\n");
            break;
        case GLUT_KEY_RIGHT:
            printf("Right arrow\n");
            break;
        case GLUT_KEY_UP:
            printf("Up arrow\n");
            break;
        case GLUT_KEY_DOWN:
            printf("Down arrow\n");
            break;
    }
}

void reshape(int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glOrtho(- w/2, (GLdouble) w/2, -h/2, (GLdouble) h/2, -1.0, 1.0); // Center at (0.0, 0.0) and scale = window size
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
    
int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (400, 100);
    
    glutCreateWindow ("It's a gwaan be space goddammit");
    
    initGL ();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeys);   // standard key is pressed/released
    glutSpecialFunc(handleSpecialKeys); // "special" key is pressed/released
    glutMouseFunc(mouse);           // mouse button pressed/released
    //glutMotionFunc(motion);         // mouse moved *while* any button is pressed
    
    glutMainLoop();
    
    return 0;   /* ISO C requires main to return int. */
}