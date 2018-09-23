#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#ifdef __linux__
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#endif
#include "button.h"
#include "transform.h"
#include "interface.h"

GLdouble eyeX = 0; 
GLdouble eyeY = 1;
GLdouble eyeZ = 6.5;
GLdouble centerX = 0;
GLdouble centerY = 0;
GLdouble centerZ = 0;
GLdouble upX = 0;
GLdouble upY = 1;
GLdouble upZ = 0;

int flagscmp(int op_flags[N_OBJECTS][N_OPS], int op_memory[N_OBJECTS][N_OPS]){
    int i = 0, j = 0;
    for(i = 0 ; i < 3 ; i++)
        for(j = 0 ; j < 4 ; j++)
        if(op_flags[i][j] != op_memory[i][j])
            return op_flags[i][j] - op_memory[i][j];
    return 0;
}

int vectorflagcmp(int op_flags[4], int op_memory[4]){
    int i = 0;
    for(i = 0 ; i < 4 ; i++)
        if(op_flags[i] != op_memory[i])
            return op_flags[i] - op_memory[i];
    return 0;
}

void setMaterial(int currentMaterial){
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

    switch (currentMaterial){
    case 0:
        // Diffuse reflection only; no ambient or specular  
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
        
    case 1:
        // Diffuse and specular reflection; low shininess; no ambient
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
        
    case 2:
        // Diffuse and specular reflection; high shininess; no ambient
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
        
    case 3:
        // Diffuse refl.; emission; no ambient or specular reflection
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
        break;
    }     
}

//Define object color
void colorObject(int oType, int SelectedObject){
    int compareObject;
    if(SelectedObject < N_OBJECTS) 
        compareObject = SelectedObject+N_OBJECTS;
    else 
        compareObject = SelectedObject;

    if(compareObject == oType)
        glColor3f(1,1,1);
    else 
        glColor3f(0,1,1);  
          
    return ;
}

//Choose objects to display
void drawObject(int oType, int currentMaterial, int SelectedObject) {
    setMaterial(currentMaterial);
    
    colorObject(oType, SelectedObject);
    
    switch(oType) {
        case SOLID_CUBE:
            glutSolidCube(1.5);
            break;
        case SOLID_SPHERE:
            glutSolidSphere(1, 100, 100);
            break;
        case SOLID_TEAPOT:
            glutSolidTeapot(1);
            break;
        case WIRE_CUBE:
            glutWireCube(1.5);
            break;
        case WIRE_SPHERE:
            glutWireSphere(1, 100, 100);
            break;
        case WIRE_TEAPOT:
            glutWireTeapot(1);
            break;
    }

    return;
}

// Draw 3D wire objects
void Draw3DWire(int SelectedObject, int op_flags[N_OBJECTS][N_OPS]){


    int material = 1;

    glViewport(400,400,400,400);
    glPushMatrix();
    gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
    translate(op_flags[0][TRANSLATE]);
    rotate(op_flags[0][ROTATE]);
    scale(op_flags[0][SCALE]);
    mirror(op_flags[0][MIRROR]);
    material = light(op_flags[0][LIGHT]);
    drawObject(WIRE_TEAPOT,material,SelectedObject);
    glPopMatrix();

    glViewport(400, 180 ,400,400);
    glPushMatrix();
    gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
    translate(op_flags[1][TRANSLATE]);
    rotate(op_flags[1][ROTATE]);
    scale(op_flags[1][SCALE]);
    mirror(op_flags[1][MIRROR]);
    material = light(op_flags[1][LIGHT]);
    drawObject(WIRE_SPHERE,material,SelectedObject);
    glPopMatrix();

    glViewport(400, -70 ,400,400);
    glPushMatrix();
    gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
    translate(op_flags[2][TRANSLATE]);
    rotate(op_flags[2][ROTATE]);
    scale(op_flags[2][SCALE]);
    mirror(op_flags[2][MIRROR]);
    material = light(op_flags[2][LIGHT]);
    drawObject(WIRE_CUBE,material,SelectedObject);
    glPopMatrix();

    return;
}

// Draw 3D solid objects
void Draw3DSolid(int SelectedObject, int op_flags[N_OBJECTS][N_OPS]){

    int material = 1;

    glViewport(400,400,400,400);
    glPushMatrix();
    gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
    translate(op_flags[0][TRANSLATE]);
    rotate(op_flags[0][ROTATE]);
    scale(op_flags[0][SCALE]);
    mirror(op_flags[0][MIRROR]);
    material = light(op_flags[0][LIGHT]);
    drawObject(SOLID_TEAPOT,material,SelectedObject);
    glPopMatrix();

    glViewport(400, 180 ,400,400);
    glPushMatrix();
    gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
    translate(op_flags[1][TRANSLATE]);
    rotate(op_flags[1][ROTATE]);
    scale(op_flags[1][SCALE]);
    mirror(op_flags[1][MIRROR]);
    material = light(op_flags[1][LIGHT]);
    drawObject(SOLID_SPHERE,material,SelectedObject);
    glPopMatrix();

    glViewport(400, -70 ,400,400);
    glPushMatrix();
    gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
    translate(op_flags[2][TRANSLATE]);
    rotate(op_flags[2][ROTATE]);
    scale(op_flags[2][SCALE]);
    mirror(op_flags[2][MIRROR]);
    material = light(op_flags[2][LIGHT]);
    drawObject(SOLID_CUBE,material,SelectedObject);
    glPopMatrix();
    
    return;
}
//Draw 2D components - butttons 
void Draw2D(ButtonList *bl){
    glViewport(0,-95,800,800);
    ButtonDraw(bl);

    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2f(0.25,210);
    glVertex2f(800,210);
    glEnd();

    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2f(0.25,470);
    glVertex2f(800,470);
    glEnd();

    return;
}



