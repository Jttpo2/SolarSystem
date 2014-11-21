//
//  main.cpp
//  SolarSystem
//
//  Created by John Petersson on 2014-11-21.
//  Copyright (c) 2014 John Petersson. All rights reserved.
//
//#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
//#include <OpenGL/glfw.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

static GLfloat spin = 0.0;

void display(void){
   glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.7, 0.1, 0.1);
    
    glBegin(GL_POLYGON);
        glVertex3f (-10.25, -10.25, 0.0);
        glVertex3f (10.75, -10.25, 0.0);
        glVertex3f (10.75, 10.75, 0.0);
        glVertex3f (-10.25, 10.75, 0.0);
    glEnd();
    
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

void init() {
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
            }
            case GLUT_RIGHT_BUTTON:
                if (state == GLUT_DOWN) {
                    glutIdleFunc(NULL);
                }
                break;
            default: break;
    }
}

void reshape(int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
    
int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (400, 100);
    glutCreateWindow ("It's a gwaan be space goddammit");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}