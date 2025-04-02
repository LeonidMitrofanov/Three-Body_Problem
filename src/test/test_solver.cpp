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

int main() {
  const char path[] = "../data/test.csv";
  vector<double> y = {1.0 / sqrt(2), 0.0};
  double t = 0.0;
  double T = 5.0;
  double h = 0.01;

  RungeKutta4 solver(testSystem, y, h);
  ofstream file(path);

  file << "t,y1_calc,y2_calc,y1_valid,y2_valid\n";
  while (t < T) {
    file << t << ',' << y[0] << ',' << y[1] << ',' << y1(t) << ',' << y2(t)
         << "\n";

    solver.step(t);
    y = solver.getState();
    t += solver.getStepSize();
  }

  file.close();
  cout << "Тестовая задача: Данные сохранены в " << path << endl;

  return 0;
}