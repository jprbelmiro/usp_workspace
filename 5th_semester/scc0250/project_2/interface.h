#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#define N_OBJECTS 3
#define N_OPS 5

typedef enum{
	SOLID_CUBE = 0,
	SOLID_SPHERE,
	SOLID_TEAPOT,
	WIRE_CUBE,
	WIRE_SPHERE,
	WIRE_TEAPOT
}object_type;

int flagscmp(int[N_OBJECTS][N_OPS], int[N_OBJECTS][N_OPS]);

int vectorflagcmp(int[N_OBJECTS], int[N_OPS]);

void setMaterial(int );

void colorObject(int , int );

void drawObject(int , int , int );

void Draw3DWire(int , int[N_OBJECTS][N_OPS]);

void Draw3DSolid(int , int[N_OBJECTS][N_OPS]);

void Draw2D(ButtonList *);

#endif
