#ifndef _MYCUBE_H_
#define _MYCUBE_H_

#define N_OBJECTS 3
#define N_OPS 5

float *normalSurface(float[3], float[3], float[3]);

void print(int , int ,int , char *);

void print_normal(int , int , float *);

float **createNormal(float[8][3]);

#endif
