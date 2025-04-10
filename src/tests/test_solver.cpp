#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "../ode_solvers/include/ode_solvers.hpp"
#include "../ode_models/include/ode_models.hpp"

using namespace std;

double y1(double x) { return cos(x) / sqrt(1 + exp(2 * x)); }
double y2(double x) { return sin(x) / sqrt(1 + exp(2 * x)); }

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <output_path>" << endl;
    return 1;
  }

  const string path = argv[1];
  vector<double> y = {1.0 / sqrt(2), 0.0};
  double t = 0.0;
  double T = 5.0;
  double h = 0.01;

  RungeKutta4 solver(testEquation, y, h);
  ofstream file(path);

  file << "t,y1_calc,y2_calc,y1_valid,y2_valid\n";
  while (t < T) {
    file << t << ',' << y[0] << ',' << y[1] << ',' << y1(t) << ',' << y2(t)
         << "\n";

    solver.make_step(h);
    y = solver.getState();
    t = solver.getParam();
  }

  file.close();
  return 0;
}