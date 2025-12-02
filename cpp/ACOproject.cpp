#include "CGraph.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  CGraph G1("../points.txt");

  G1.ACO(25, 2500);
}
