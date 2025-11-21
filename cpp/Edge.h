#ifndef EDGE
#define EDGE

#include <cmath>

#include "Point.h"

class Edge {  // edge between two points containing distance and pheromones
 public:
  Edge(double d) { dist = d; };
  Edge(double d, double p) {
    dist = d;
    pher = p;
  };
  Edge(Point* p1, Point* p2) { findDist(p1, p2); };
  void findDist(Point* p1, Point* p2) {
    double difx = (p2->x - p1->x);
    double dify = (p2->y - p1->y);
    dist = sqrt((pow(difx, 2)) + (pow(dify, 2)));
  }
  ~Edge() {};

  double dist = 0;  // distance between two points
  double pher = 0;  // pheromone value
};

#endif