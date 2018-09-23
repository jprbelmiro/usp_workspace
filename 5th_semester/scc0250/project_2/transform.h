#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

typedef enum{
	ROTATE = 0,
	TRANSLATE,
	SCALE,
	MIRROR,
	LIGHT
}transformations;

void rotate(int );

void translate(int );

void scale(int );

void mirror(int );

int light(int );

#endif
