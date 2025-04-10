#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "../ode_solvers/include/ode_solvers.hpp"
#include "../ode_models/include/ode_models.hpp"

using namespace std;

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
  double step_size = 1e-3;
  double m = 0.012277471;
  double M = 1 - m;

  RungeKutta4 solver(threeBodyEquation, state, 0);

  ofstream file(path);
  file << "t,x,y,vx,vy\n";

  while (t < T) {
    file << t << "," << state[0] << "," << state[1] << "," << state[2] << ","
         << state[3] << "\n";

    if (abs(state[0] + m) < 0.1 || abs (state[0] - M) < 0.1)
      solver.make_step(step_size/10.0);
    else
      solver.make_step(step_size);
    state = solver.getState();
    t = solver.getParam();
  }

  file.close();
  return 0;
}