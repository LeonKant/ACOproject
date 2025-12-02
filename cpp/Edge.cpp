
#include "Edge.h"
#include <cmath>

void Edge::findDist(Point *p1, Point *p2) {
  double difx = (p2->x - p1->x);
  double dify = (p2->y - p1->y);
  dist = sqrt((pow(difx, 2)) + (pow(dify, 2)));
}