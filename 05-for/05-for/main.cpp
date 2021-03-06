//
//  main.cpp
//  05-for
//
//  Created by Yoshihisa Kaino on 2020/06/07.
//  Copyright © 2020 yoshi1125hisa. All rights reserved.
//

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

float rotation = 1.0;

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, (double)width/height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.1);
}

void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    float x = 10;
    float y = 10;
    float z = 10;
    
    glPushMatrix();
    glTranslatef(-x+0.1 / 0.2, 0.1, -1.0);
    glRotatef(rotation, 0.0, 1.0, 0.0);
    
    for(int i=0; i<x; i++){
        glPushMatrix();
        for(int j=0; j<y; j++){
            glPopMatrix();
            glPushMatrix();
            glRotatef(rotation, 0.1, 0.2, 0.1);
            for(int k=0; k<z; k++){
                glPushMatrix();
                glTranslatef(i, j, k);
                if (i % 2 == 0){
                    glutSolidCube(0.2);
                }else{
                    glutSolidCube(0.6);
                }
                glPopMatrix();
            }
        }
    }
    
    glPopMatrix();
    glutSwapBuffers();
}

void setup(){
    float lightPosition[4] = {5.25, 2.0, 0.25, 1.0};
    float ambient[4] = {0.3, 0.5, 0.0, 1.0};
    float diffuse[4] = {1.0, 1.0, 0.0, 1.0};
    float specular[4] = {1.0, 1.0, 1.0, 1.0};
    float shininess[1] = {20.0};
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void idle(){
    rotation = rotation + 1;
    glutPostRedisplay();
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("forCubes");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    setup();
    
    glutMainLoop();
    return 0;
}


