#ifndef POINT
#define POINT

class Point { // individual coordinate point
public:
  Point(double num1, double num2) : x(num1), y(num2) {};
  ~Point() {};
  double x, y, p = 0; // coordinate point and probability
};

#endif