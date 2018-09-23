#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
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
#include "mouse.h"
#include "button.h"
#include "interface.h"
#include "mycube.h"

//Mouse global
Mouse TheMouse = {0,0,0,0};
//Buttons global
ButtonList *bl = NULL;

//Window scale
int win[2];
int winw = 800;
int winh = 800;
int winw2 = 800;
int winh2 = 800;

//Switch Objects
int SelectedObject = 0;

//Switch lighting model
int curShading = 0;

//Switch to Solid model
int SolidMode = 0;

//Switch view mode
int View = 0;

//Light Position
GLfloat light_position[4] = {400.0, 800.0, -20.0, 10.0};

//Object Operation Counter and flags
int op_flags[3][5] = {{0,0,3,0,0},{0,0,3,0,0},{0,0,3,0,0}};
double rotate_y = 0, rotate_x = 0;

//Normal vec
float **normal = NULL;
float v[8][3] = {{-0.5 , -0.5, -0.5},
				{-0.5 , -0.5, 0.5},
				{-0.5 , 0.5, -0.5},
				{-0.5 , 0.5, 0.5},
				{0.5 , -0.5, -0.5},
				{0.5 , -0.5, 0.5},
				{0.5 , 0.5, -0.5},
				{0.5 , 0.5, 0.5}};

//Control keyboard events
void exitEvent(unsigned char key, int x, int y) {
	if(key == '\x1b')
            exit(0);
}

//Control keyboard events
void keyPressEvent(unsigned char key, int x, int y) {
    switch(key) {
        case '.' :
	        SelectedObject +=1;
	        if(SelectedObject == 6) SelectedObject = 0;
	        	glutPostRedisplay();
        	break;
        case '\x1b' :
            exit(0);
            break;
       	case 't':
       		printf("Texture Changed.\n");
       		if (SolidMode){curShading += 1;
            curShading %= 2;}
       		glutPostRedisplay();
       		break;
       	case 'T':
       		printf("Texture Changed.\n");
       		if (SolidMode){curShading += 1;
            curShading %= 2;}
       		glutPostRedisplay();
       		break;
       	case 's':
       		printf("Solid Mode Changed.\n");
       		SolidMode += 1;
            SolidMode %= 2;
       		glutPostRedisplay();
       		break;
       	case 'S':
       		printf("Solid Mode Changed.\n");
       		SolidMode += 1;
            SolidMode %= 2;
       		glutPostRedisplay();
       		break;
       	case 'p':
       		printf("View Mode Changed.\n");
       		View += 1;
       		View %= 2;
       		glutPostRedisplay();
       		break;
       	case 'P':
       		printf("View Mode Changed.\n");
       		View += 1;
       		View %= 2;
       		glutPostRedisplay();
       		break;

    }
}

void specialKeys( int key, int x, int y ) {
 
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 5;
 
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 5;
 
  else if (key == GLUT_KEY_UP)
    rotate_x += 5;
 
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 5;

  else if (key == '\x1b')
    exit(0);
 
  glutPostRedisplay();
 
}


//Mouse button control
void MouseButton(int button,int pressed,int x, int y){
	//update position
	TheMouse.x = x;
	TheMouse.y = y;

	if (pressed == GLUT_DOWN){ //press
		switch(button){
			case GLUT_LEFT_BUTTON:
				TheMouse.lb = 1;
				ButtonSetPress(bl,x,y,op_flags);
			case GLUT_RIGHT_BUTTON:
				TheMouse.rb = 1;
				break;
		}
	}
	else { //button released
		switch(button) {
			case GLUT_LEFT_BUTTON: 
				TheMouse.lb = 0;
				ButtonRestore(bl,x,y);
				break;
			case GLUT_RIGHT_BUTTON:
				TheMouse.rb = 0;
				break;
		}
	}

	glutPostRedisplay();
}

//Mouse moving callback
void MouseMotion(int x, int y){
	//mouse position update
	TheMouse.x = x;
	TheMouse.y = y;

	//Verify if it is under object
	ButtonUnder(bl,TheMouse.x,TheMouse.y);

	glutPostRedisplay();
}

// Define light position
void setLight() {
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    return;
}

// Define Flat, Gouraud or Phong lightning
void setShading(int sType) {
    switch(sType) { 
        case 0 :
            glShadeModel(GL_SMOOTH); //Gouraud
            break;            
        case 1 :
            glShadeModel(GL_FLAT); //Flat
            break;
    }
}

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void setLightPhong() {
    GLfloat light_position[4] = {10.0, 10.0, -20.0, 10.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void displayPhong(){
	int xt = 100, yt = 670, zt = 200;
  	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
	glEnable(GL_DEPTH_TEST);
	initLighting();
	print(xt+100,yt,zt, "           Normals");
	print(xt+100,yt-20,zt, "_________________");
	print(xt,yt,zt, "Faces");
	print(xt,yt-20,zt, "______");
	print(xt,yt-40,zt, "Azul");
	print(xt,yt-60,zt, "Branco");
	print(xt,yt-80,zt, "Roxo");
	print(xt,yt-100,zt, "Verde");
	print(xt,yt-120,zt, "Amarelo");
	print(xt,yt-140,zt, "Vermelho");
	print_normal(xt+100,yt-40,normal[0]);
	print_normal(xt+100,yt-60,normal[1]);
	print_normal(xt+100,yt-80,normal[2]);
	print_normal(xt+100,yt-100,normal[3]);
	print_normal(xt+100,yt-120,normal[4]);
	print_normal(xt+100,yt-140,normal[5]);

	print(xt+400,yt-100,zt, "Rotate: KEYBOARD");
	print(xt+400,yt-120,zt, "[UP | DOWN |LEFT | RIGHT]");

	glViewport( 0, 0 ,600,600);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	  
	glLoadIdentity();
		  
	gluPerspective(45,2,1,100);
	glLoadIdentity();
	setLight();
	glShadeModel(GL_FLAT);

	//Rotate when user change rotate_x or rotate_y
	glRotatef( rotate_x, 1.0, 0.0, 0.0 );
	glRotatef( rotate_y, 0.0, 1.0, 0.0 );
 
 
  	//Front - Blue
 	glBegin(GL_POLYGON);
   	glColor3f(   0.0,  0.0,  1.0 );
  	glVertex3f( v[4][0], v[4][1], v[4][2] );      
  	glVertex3f( v[6][0], v[6][1], v[6][2] );      
  	glVertex3f( v[2][0], v[2][1], v[2][2] );      
  	glVertex3f( v[0][0], v[0][1], v[0][2] );      
 
  	glEnd();
 
	//Back - White
 	glBegin(GL_POLYGON);
 	glColor3f(   1.0,  1.0,  1.0 );
  	glVertex3f( v[5][0], v[5][1], v[5][2] );
  	glVertex3f(  v[7][0], v[7][1], v[7][2] );
  	glVertex3f( v[3][0], v[3][1], v[3][2] );
  	glVertex3f( v[1][0], v[1][1], v[1][2] );
  	glEnd();
 
  	//Right - Purple
 	glBegin(GL_POLYGON);
  	glColor3f(  1.0,  0.0,  1.0 );
  	glVertex3f( v[4][0], v[4][1], v[4][2] );
  	glVertex3f( v[6][0], v[6][1], v[6][2] );
  	glVertex3f( v[7][0], v[7][1], v[7][2] );
  	glVertex3f( v[5][0], v[5][1], v[5][2] );
  	glEnd();
 
  	//Left - Green
 	glBegin(GL_POLYGON);
  	glColor3f(   0.0,  1.0,  0.0 );
  	glVertex3f( v[1][0], v[1][1], v[1][2] );
  	glVertex3f( v[3][0], v[3][1], v[3][2] );
  	glVertex3f( v[2][0], v[2][1], v[2][2] );
  	glVertex3f( v[0][0], v[0][1], v[0][2] );
  	glEnd();
 
  	//Top - Yellow
 	glBegin(GL_POLYGON);
  	glColor3f(   1.0,  1.0,  0.0 );
  	glVertex3f( v[7][0], v[7][1], v[7][2] );
  	glVertex3f( v[6][0], v[6][1], v[6][2] );
  	glVertex3f( v[2][0], v[2][1], v[2][2] );
  	glVertex3f( v[3][0], v[3][1], v[3][2] );
  	glEnd();
 
  	//Base - Red
 	glBegin(GL_POLYGON);
	glColor3f(   1.0,  0.0,  0.0 );
	glVertex3f(  v[4][0], v[4][1], v[4][2] );
  	glVertex3f(  v[5][0], v[5][1], v[5][2] );
  	glVertex3f( v[1][0], v[1][1], v[1][2] );
	glVertex3f( v[0][0], v[0][1], v[0][2] );
	glEnd();
	
	glFlush();
	glutSwapBuffers();
}

// Draw elements
void display(){
	//clear z buffer and background
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//enable light and z-buffer
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	//set matrix mode for 3D elements
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(View == 0)
		gluPerspective(45,(winh==0)?(1):((float)winw/winh),1,100);
	else
		glOrtho(-5,5,-5,5,-50,50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setLight();
    setShading(curShading);

	if(SolidMode)
	   	Draw3DSolid(SelectedObject,op_flags);
	else
	    Draw3DWire(SelectedObject,op_flags);
	    	
	//disable z-buffer for 2D elements
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	//set matrix mode for 2D elements
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,winw,winh,0,0,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Draw2D(bl);

	glutSwapBuffers();

	return;
}

// Main function
int main(int argc,char **argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
	printf("Defined variables\n");

	//Main window settings
	glutInitWindowSize(winw,winh);
	glutInitWindowPosition(0,100);
	win[0] = glutCreateWindow("Trabalho 2");
	printf("Window1 (%d) ok\n",win[0]);

  	//Interaction functions
  	glutSetWindow(win[0]);
  	printf("Window1Set ok\n");
	glutMouseFunc(MouseButton);
	printf("MouseButton1 ok\n");
	glutPassiveMotionFunc(MouseMotion);
	printf("MotionMotion1 ok\n");
	glutKeyboardFunc(keyPressEvent);
	printf("Keyboard1 ok\n");
	ButtonList *buttonl = init();
	bl = buttonl;
	glutDisplayFunc(display);
	printf("Display1 ok\n");


	//Phong window settings
	glutInitWindowSize(winw2,winh2);
	glutInitWindowPosition(800,100);
	win[1] = glutCreateWindow("Super Cube");
  	printf("Window2 (%d) ok\n",win[1]);

	glutSetWindow(win[1]);
  	printf("Window2Set ok\n");
	initLighting();
  	printf("Light2 ok\n");
	normal = createNormal(v);
  	printf("Normal2 ok\n");
	glutDisplayFunc(displayPhong);
  	printf("Diplay2 ok\n");
  	setLightPhong();
  	printf("LightSet2 ok\n");
  	glutKeyboardFunc(exitEvent);
  	glutSpecialFunc(specialKeys);
  	printf("Interaction2 ok\n");

	glutMainLoop();

	return 0;
}
