#include "CGraph.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  int size = 50; // # of points in input file
  CGraph G1(size);
  string line, s, x, y;
  fstream myFile;

  myFile.open("../points.txt");
  int i = 1;
  while (getline(myFile, line)) {
    istringstream s(line);
    while (s >> x && s >> y) {
      Point *newPoint = new Point(stoi(x), stoi(y));
      G1.addPoint(newPoint);
    }
    ++i;
  }
  G1.compGraph();
  myFile.close();

  G1.ACO();
}
