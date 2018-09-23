#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __linux__
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#endif

char str[100];
 
float *normalSurface(float v1[3], float v2[3], float v3[3]){
	float AB[3] = {v1[0] - v2[0],v1[1] - v2[1],v1[2] - v2[2]};
  	float AC[3] = {v1[0] - v3[0],v1[1] - v3[1],v1[2] - v3[2]};

  	float *Normal = (float *)malloc(sizeof(float)*3);

  	Normal[0] = (AB[1]*AC[2] - AB[2]*AC[1]);
  	Normal[1] = (AB[0]*AC[2] - AB[2]*AC[0]);
  	Normal[2] = (AB[0]*AC[1] - AB[1]*AC[0]);

	return Normal;
}

void print(int x, int y,int z, char *string){
  	glDisable(GL_LIGHTING);
  	glViewport(x,y, 30, 30);
  	glColor3f( 1, 1, 1 );
  	glRasterPos2f(0,0);

  	int len = (int) strlen(string);

  	for (int i = 0; i < len; i++){ 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
		glEnable(GL_LIGHTING);
  	}

  	return;
}

void print_normal(int x, int y,float *normal){
  	sprintf(str, "%.2f", normal[0]);
  	print(x, y,100, str);

  	sprintf(str, "%.2f", normal[1]);
  	print(x+80, y,100, str);

  	sprintf(str, "%.2f", normal[2]);
	print(x+160, y,100, str);
  	return;
}

float **createNormal(float v[8][3]){
	float **normal = (float **)malloc(sizeof(float *)*6);

   normal[0] = normalSurface(v[0],v[4],v[2]);
   normal[1] = normalSurface(v[1],v[5],v[7]);
   normal[2] = normalSurface(v[4],v[5],v[6]);
   normal[3] = normalSurface(v[0],v[1],v[2]);
   normal[4] = normalSurface(v[2],v[3],v[6]);
   normal[5] = normalSurface(v[0],v[1],v[4]);

	return normal;
}