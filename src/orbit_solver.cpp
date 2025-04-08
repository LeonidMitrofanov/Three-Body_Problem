#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "../ODESolvers/include/RungeKutta4.hpp"

using namespace std;

vector<double> threeBodySystem(double t, const vector<double>& a) {
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

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <output_path>" << endl;
    return 1;
  }

  const string path = argv[1];
  double x, y, vx, vy;
  x = 0.994, y = 0.0, vx = 0.0, vy = -2.031732629557337;
  vector<double> state = {x, y, vx, vy};
  double t = 0.0;
  double T = 11.124340337;
  double h_initial = 1e-3;

  RungeKutta4 solver(threeBodySystem, state, 0);

  ofstream file(path);
  file << "t,x,y,vx,vy\n";

  while (t < T) {
    file << t << "," << state[0] << "," << state[1] << "," << state[2] << ","
         << state[3] << "\n";

    solver.make_step(h_initial);
    state = solver.getState();
    t = solver.getParam();
  }

  file.close();
  return 0;
}