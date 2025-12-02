#ifndef CGRAPH
#define CGRAPH

#include "Edge.h"
#include "Point.h"

#include <vector>
using namespace std;

class CGraph { // graph of "cities"
public:
  CGraph(int num);
  ~CGraph() {};
  void addPoint(Point *p);
  void compGraph(); // create complete graph
  void ACO();       // ACO algorithm
  int wrandPoint(vector<int> &P1);
  void assignProb(int curr, vector<int> &P1);

  vector<vector<Edge *>> E;
  vector<Point *> P;
};

#endif