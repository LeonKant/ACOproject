#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Point {//individual coordinate point
public:
    Point(double num1, double num2) { x = num1; y = num2; };
    Point(double num1, double num2, bool v) { x = num1; y = num2; visited = v; };
    double x, y = 0;//coordinate point
    bool visited = 0;//visited or not
    
};
class Edge {//edge between two points containing distance and pheromones
public:  
    Edge(double d) { dist = d; };
    Edge(double d, int p) { dist = d; pher = p; };
    Edge(Point p1, Point p2) { findDist(p1, p2); };
    void findDist(Point p1, Point p2) {

        double difx = (p2.x - p1.x);
        double dify = (p2.y - p1.y);
        dist = sqrt((pow (difx, 2)) + (pow (dify, 2)));
    }
    ~Edge() {};

    double dist = 0;//distance between two points
    int pher = 0;//pheromone value
    
};

class CGraph {
public:
    CGraph() {};
    CGraph(int num) { 
        E.resize(num); 
        vector<Edge*> e(E.size());

        for (int i = 0; i < E.size(); ++i) {
            E[i] = e;
        }
    };
    ~CGraph() {};
    void addPoint(Point p) { P.push_back(p); };
    void compGraph(); // create complete graph

    vector<vector<Edge*>> E;
    vector<Point> P;
};

void CGraph::compGraph() {
    int j = 0;
    for (int i = 0; i < E.size(); ++i) {
        for (j = i; j < E.size(); ++j) {
            if (i == j) {
                Edge* e = new Edge(0);
                E[i][j] = e;
            }
            else{
            Edge* e = new Edge(P[i],P[j]);
            E[i][j] = e;
            E[j][i] = e;
            }
        }
    }


}

int main(){
    Point p0 (1, 2);
    Point p1 (3, 5);
    Point p2 (6, 4);
    Point p3 (7, 2);
    CGraph G1(4);
    //Point p4 (5, 11);
    //vector<vector<Edge>> Edges;
    //vector<Point> Points;

    G1.addPoint(p0);
    G1.addPoint(p1);
    G1.addPoint(p2);
    G1.addPoint(p3);
    
    G1.compGraph();
    
    for (int i = 0; i < 4; ++i) {
        cout << G1.P[i].x << ", " << G1.P[i].y << endl;
    }

    int j = 0;
    for (int i = 0; i < G1.E.size(); ++i) {
        for (j = i; j < G1.E.size(); ++j) {
            cout << G1.E[i][j]->dist << " ";
        }
        cout << endl;
    }

}


