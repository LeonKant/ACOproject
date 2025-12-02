#include "CGraph.h"

#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

CGraph::CGraph(string pointsDir) {
  string line, s, x, y;
  fstream file;

  file.open(pointsDir);

  if (!file) {
    throw -1;
  }

  while (getline(file, line)) {
    istringstream s(line);
    while (s >> x && s >> y) {
      Point *newPoint = new Point(stoi(x), stoi(y));
      addPoint(newPoint);
    }
  }
  compGraph();
  file.close();
}
void CGraph::addPoint(Point *p) { P.push_back(p); };

void CGraph::compGraph() { // create complete graph
  E.resize(P.size(), vector<Edge *>(P.size()));
  int j = 0;
  for (int i = 0; i < E.size(); ++i) {
    for (j = i; j < E.size(); ++j) {
      if (i == j) {
        Edge *e = new Edge(0);
        E[i][j] = e;
      } else {
        Edge *e = new Edge(P[i], P[j]);
        E[i][j] = e;
        E[j][i] = e;
      }
    }
  }
}

int CGraph::wrandPoint(
    vector<int> &P1) { // determine random point based on probability
  vector<double> CDF;  // discrete cumulative density function
  double prev = 0;
  double x;

  for (int i = 0; i < P1.size(); ++i) { // cumulative probability distribution
    prev = prev + P[P1[i]]->p;
    CDF.push_back(prev);
  }

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator(seed);
  uniform_real_distribution<double> distribution(0.0, 1.0);

  x = distribution(generator); // generate number between 0 and 1

  int l = 0;
  int r = CDF.size() - 1;

  while (l < r) { // binary search
    int m = (l + r) / 2;

    if (CDF[m] > x) {
      r = m;
    } else {
      l = m + 1;
    }
  }

  return r;
}

void CGraph::assignProb(
    int curr, vector<int> &P1) { // assign probabilities to possible edges
  double t, n;
  double denom = 0;
  double a = 1;
  double b = 1.5;

  for (int i = 0; i < P1.size(); ++i) {
    t = E[curr][P1[i]]->pher;
    n = 1 / E[curr][P1[i]]->dist;

    denom = denom + (pow(t, a) * pow(n, b));
  }

  for (int i = 0; i < P1.size(); ++i) {
    t = E[curr][P1[i]]->pher;
    n = 1 / E[curr][P1[i]]->dist;

    P[P1[i]]->p = (pow(t, a) * pow(n, b)) / denom;
  }
}

void CGraph::ACO(int ants, int maxJourneys) {
  int journeys = 0;
  vector<Edge *> min;
  string avgPathDirName =
      "_output/" + to_string(ants) + "a" + to_string(maxJourneys) + "jb.txt";
  ofstream myFile("_output/ant_paths.txt");
  ofstream myFile1(avgPathDirName); // file to store avg path length per journey

  while (journeys < maxJourneys) { // # of journeys
    vector<vector<Edge *>> S;
    for (int i = 0; i < ants; ++i) {
      vector<Edge *> s;         // series of edges; path
      vector<int> P1(P.size()); // contains indexes of traversable points
      int curr = 0;             // current city initialized to 0

      for (int l = 0; l < P1.size(); ++l) { // point indexes; N(s)
        P1[l] = l;
      }
      for (int j = 0; j < P.size(); ++j) { // while N(s)
        if (j == 0) {                      // starts at point 0
          P1.erase(P1.begin());
          myFile << curr << " ";
        } else {
          double d = P1.size();
          double p = 1 / d;
          double newPoint;

          Edge *c = nullptr;

          if (j != 0 && E[0][1]->pher == 0) { // if pheromone values are 0,
                                              // equal chance of choosing path
            for (int k = 0; k < P1.size(); ++k) {
              P[P1[k]]->p = p;
            }
          } else { // assign probability
            assignProb(curr, P1);
          }

          int np = wrandPoint(P1);
          newPoint = P1[np];

          c = E[curr][newPoint]; // c <- Choose from N(s)
          s.push_back(c);        // Append c to s

          curr = newPoint;
          myFile << curr << " ";

          P1.erase(P1.begin() + np);
        }
      }

      s.push_back(E[curr][0]);
      myFile << "0" << endl;
      S.push_back(s);
      s.clear();
      P1.clear();
    }
    myFile << endl;

    // pheromone update
    vector<double> antPath(ants);
    double minVal = 0;

    if (E[0][1]->pher == 0) { // first journey
      double sum;
      double avg;
      double fullSum = 0;
      for (int i = 0; i < S.size(); ++i) {
        sum = 0;
        avg = 0;
        for (int j = 0; j < S[i].size(); ++j) { // sum of edges in a solution
          antPath[i] = antPath[i] + S[i][j]->dist;
          sum = sum + S[i][j]->dist;
        }

        if (minVal == 0) { // determine shortest solution so far
          minVal = sum;
          min = S[i];
        } else if (sum < minVal) {
          minVal = sum;
          min = S[i];
        }

        for (int j = 0; j < S[i].size(); ++j) { // pheromone distribution
          double pheromones = S[i][j]->pher + (1 / antPath[i]);
          S[i][j]->pher = pheromones;
        }
        fullSum = fullSum + sum;
      }
      avg = fullSum / double(ants);
      myFile1 /*<< "min: " << minVal << " avg: "*/ << avg << endl;

      for (int i = 0; i < E.size();
           ++i) { // off chance that pheromone is still 0
        for (int j = 0; j < E[i].size(); ++j) {
          if (E[i][j]->pher == 0 && i != j) {
            E[i][j]->pher = 1 / avg;
          }
        }
      }
    } else { // after first journey
      double sum;
      double avg;
      double fullSum = 0;

      for (int i = 0; i < S.size(); ++i) {
        sum = 0;
        avg = 0;
        for (int j = 0; j < S[i].size(); ++j) {
          antPath[i] = antPath[i] + S[i][j]->dist;
          sum = sum + S[i][j]->dist;
        }
        if (minVal == 0) { // determine shortest solution so far
          minVal = sum;
          min = S[i];
        } else if (sum < minVal) {
          minVal = sum;
          min = S[i];
        }
        for (int j = 0; j < S[i].size(); ++j) {
          S[i][j]->pher = S[i][j]->pher + (1 / antPath[i]);
        }
        fullSum = fullSum + sum;
      }
      avg = fullSum / double(ants);
      myFile1 << avg << endl;
    }
    antPath.clear();
    ++journeys;
  }
  myFile.close();
  myFile1.close();
}