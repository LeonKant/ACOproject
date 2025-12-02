#ifndef CGRAPH
#define CGRAPH

#include "Edge.h"
#include "Point.h"

#include <vector>
using namespace std;

class CGraph { // graph of "cities"
public:
  CGraph() {};
  CGraph(int size) : P(size), E(size, vector<Edge *>(size)) {};
  CGraph(string pointsDir);
  ~CGraph() {};
  void ACO(int numAnts, int maxJourneys); // ACO algorithm
  void addPoint(Point *p);
  void compGraph(); // create complete graph
  vector<vector<Edge *>> E;
  vector<Point *> P;

private:
  int wrandPoint(vector<int> &P1);
  void assignProb(int curr, vector<int> &P1);
};

#endif