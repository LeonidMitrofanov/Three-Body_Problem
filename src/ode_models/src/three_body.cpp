#include "../include/ode_models.hpp"

using namespace std;

vector<double> threeBodyEquation(double t, const vector<double>& a) {
    double x = a[0];
    double y = a[1];
    double vx = a[2];
    double vy = a[3];
  
    double m = 0.012277471;
    double M = 1 - m;
  
    double R1 = pow((x + m) * (x + m) + y * y, 1.5);
    double R2 = pow((x - M) * (x - M) + y * y, 1.5);
  
    double ax = x + 2 * vy - (M / R1) * (x + m) - m * (x - M) / R2;
    double ay = y - 2 * vx - (M / R1) * y - m * y / R2;
  
    return {vx, vy, ax, ay};
  }