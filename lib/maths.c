#include "include/maths.h"

/* Linear intepolate between 2 values, with interpolation distanec*/
float lerp(int start, int end, float t)
{
  return ((float)start + (t * ((float)end-(float)start)));
}

/* Lerp between two 2D float points */
Vec2df lerpPoint(Vec2df p0, Vec2df p1, float t) {
  Vec2df p = {
    lerp(p0.x, p1.x, t),
    lerp(p0.y, p1.y, t)
  };

  return p;
}

/* Diagonal distance between two 2D float points */
int diagonalDistance(Vec2df p0, Vec2df p1) {
    float dx = p1.x - p0.x;
    float dy = p1.y - p0.y;
    if (abs(dx)>abs(dy))
    {
      return abs(dx);
    }else if(abs(dy)>abs(dx))
    {
      return abs(dy);
    }else{
      return abs(dx);
    }
}

/* Round 2D float point to a 2D integer point */
Vec2di roundPoint(Vec2df p)
{
  Vec2di point;
  // point.x=(p.x - floor(p.x) > 0.5) ? ceil(p.x) : floor(p.x);
  // point.y=(p.y - floor(p.y) > 0.5) ? ceil(p.y) : floor(p.y);
  point.x=round(p.x);
  point.y=round(p.y);
  return point;
}