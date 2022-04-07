#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>
using namespace std;

class Point {//individual coordinate point
public:
    //Point(double num1) { p = num1; };
    Point(double num1, double num2) { x = num1; y = num2; };
    Point(double num1, double num2, bool v) { x = num1; y = num2; visited = v; };
    double x, y, p = 0;//coordinate point
    bool visited = 0;//visited or not

    
};
class Edge {//edge between two points containing distance and pheromones
public:  
    Edge(double d) { dist = d; };
    Edge(double d, int p) { dist = d; pher = p; };
    Edge(Point* p1, Point* p2) { findDist(p1, p2); };
    void findDist(Point* p1, Point* p2) {

        double difx = (p2->x - p1->x);
        double dify = (p2->y - p1->y);
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
    void addPoint(Point* p) { P.push_back(p); };
    void compGraph(); // create complete graph
    void ACO();// ACO algorithm
    int wrandPoint(vector<int> &P1);

    vector<vector<Edge*>> E;
    vector<Point*> P;
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

int CGraph::wrandPoint(vector<int> &P1) {
    vector<double> CDF;//discrete cumulative density function
    double prev = 0;
    double x;

    for (int i = 0; i < P1.size(); ++i) {//cumulative probability distribution
        prev = prev + P[P1[i]]->p;
        CDF.push_back(prev);
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0.0, 1.0);

    x = distribution(generator); //generate number between 0 and 1

    int l = 0; 
    int r = CDF.size() - 1;

    while (l < r) {//binary search
        int m = (l + r) / 2;
   
        if (CDF[m] > x) {
            r = m;
        }
           
        else {
            l = m + 1;
        }          
    }

    return r;
}

void CGraph::ACO() {
    int h = 0;
    while (h < 10) {
        vector<vector<Edge*>> S;

        for (int i = 0; i < 2; ++i) {//# of ants
            vector<Edge*> s;//series of edges; path
            vector<int> P1(P.size());//contains indexes of traversable points
            int curr = 0; //current city

            for (int l = 0; l < P1.size(); ++l) {//point indexes; N(s)
                P1[l] = l;
            }
            for (int j = 0; j < P.size(); ++j) {//while N(s)
                if (j == 0) {//starts at point 0
                    P1.erase(P1.begin());
                    cout << curr << " ";
                }
                else {//if pheromone values are 0, equal chance of choosing path
                    double d = P1.size();
                    double p = 1 / d;
                    double newPoint;

                    Edge* c = nullptr;

                    if (j != 0 && E[0][1]->pher == 0){//assign probability
                        for (int k = 0; k < P1.size(); ++k) {
                            P[P1[k]]->p = p;
                        }
                    }
                    else {

                    }

                    int np = wrandPoint(P1);
                    newPoint = P1[np];

                    c = E[curr][newPoint]; //c <- Choose from N(s)
                    s.push_back(c);// Append c to s

                    curr = newPoint;
                    cout << curr << " ";

                    P1.erase(P1.begin()+np);
                }
            }
            s.push_back(E[curr][0]);
            cout << "0" << " " << endl;
            S.push_back(s);
            s.clear();
            P1.clear();
        }
    }
}
int main(){

    int size = 4;
    CGraph G1(size);
    string line, s, x, y;

    ifstream inFile;
    inFile.open("points.txt");
    int i = 1;
    while (getline(inFile, line)) {
        istringstream s(line);
        while (s >> x && s >> y) {
            Point* newPoint = new Point(stoi(x), stoi(y));
            G1.addPoint(newPoint);
        }
        ++i;
    }
    G1.compGraph();
    inFile.close();
    for (int i = 0; i < 4; ++i) {
        cout << G1.P[i]->x << ", " << G1.P[i]->y << endl;
    }

    G1.ACO();

    int j = 0;
    for (int i = 0; i < G1.E.size(); ++i) {
        //int l = i;
        for (j = i; j < G1.E.size(); ++j) {
            cout << G1.E[i][j]->dist << "     ";
            
        }
        cout << endl;
        
    }
    /*int r = rand() % 100;
    cout << r << endl;*/
}
