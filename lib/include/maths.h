#ifndef MATHS_H
#define MATHS_H

#include <math.h>

/* 2D float vector */
typedef struct{
  float x,y;
}Vec2df;

/* 2D integer vector (used by cge.h for drawing calculation simplification) */
typedef struct{
  int x,y;
}Vec2di;

/* Linear intepolate between 2 values, with interpolation distanec*/
float lerp(int start, int end, float t);
/* Lerp between two 2D float points */
Vec2df lerpPoint(Vec2df p0, Vec2df p1, float t);
/* Diagonal distance between two 2D float points */
int diagonalDistance(Vec2df p0, Vec2df p1);
/* Round 2D float point to a 2D integer point */
Vec2di roundPoint(Vec2df p);

#endif