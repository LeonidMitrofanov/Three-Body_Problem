#include "../include/ode_models.hpp"

using namespace std;

vector<double> testEquation(double t, const vector<double>& y) {
    double y1 = y[0];
    double y2 = y[1];
  
    double dy1dt = -y2 + y1 * (y1 * y1 + y2 * y2 - 1);
    double dy2dt = y1 + y2 * (y1 * y1 + y2 * y2 - 1);
  
    return {dy1dt, dy2dt};
  }  