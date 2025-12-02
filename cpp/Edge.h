#ifndef EDGE
#define EDGE

#include <cmath>

#include "Point.h"

class Edge { // edge between two points containing distance and pheromones
public:
  Edge(double d) : dist(d) {};
  Edge(double d, double p) : dist(d), pher(p) {};
  Edge(Point *p1, Point *p2) { findDist(p1, p2); };
  void findDist(Point *p1, Point *p2);
  ~Edge() {};

  double dist = 0; // distance between two points
  double pher = 0; // pheromone value
};

#endif