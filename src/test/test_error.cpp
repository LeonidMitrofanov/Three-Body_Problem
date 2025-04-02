#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "../../ODESolver/include/ODESolvers.hpp"

using namespace std;

vector<double> testSystem(double t, const vector<double>& y) {
  double y1 = y[0];
  double y2 = y[1];

  double dy1dt = -y2 + y1 * (y1 * y1 + y2 * y2 - 1);
  double dy2dt = y1 + y2 * (y1 * y1 + y2 * y2 - 1);

  return {dy1dt, dy2dt};
}

double y1(double x) { return cos(x) / sqrt(1 + exp(2 * x)); }
double y2(double x) { return sin(x) / sqrt(1 + exp(2 * x)); }

double get_error(double h) {
  vector<double> y = {1.0 / sqrt(2), 0.0};
  double t = 0.0;
  double T = 5.0;
  RungeKutta4 solver(testSystem, y, h);

  double error = 0;
  while (t < T) {
    error += abs(y1(t) - y[0]) + abs(y2(t) - y[1]);
    solver.step(t);
    y = solver.getState();
    t += solver.getStepSize();
  }
  return error;
}

int main() {
  const char path[] = "../data/test_error.csv";
  double error, error_h4;
  double step = 1e-3;

  ofstream file(path);
  file << "h,e,e/h^4\n";

  for (double h = step; h < 1; h += step) {
    error = get_error(h);
    error_h4 = error / pow(h, 4);
    file << h << ',' << error << ',' << error_h4 << "\n";
  }
}