#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "../../ODESolvers/include/RungeKutta4.hpp"

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

vector<double> get_error(double h) {
  vector<double> y = {1.0 / sqrt(2), 0.0};
  double t_cur = 0.0;
  double t_end = 5.0;
  RungeKutta4 solver(testSystem, y, 0);

  double error_y1 = 0;
  double error_y2 = 0;
  while (t_cur < t_end) {
    error_y1 = max(error_y1, abs(y1(t_cur) - y[0]));
    error_y2 = max(error_y2, abs(y2(t_cur) - y[1]));
    solver.make_step(h);
    y = solver.getState();
    t_cur = solver.getParam();
  }
  return {error_y1, error_y2};
}

int main(int argc, char* argv[]) {
  // Проверка наличия аргумента
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <output_path>" << endl;
    return 1;
  }
  const string path = argv[1];

  vector<double> errors;
  double errors_h4_y1, errors_h4_y2;
  double step = 2e-3;

  ofstream file(path);
  file << "h,e_y1,e_y1/h^4,e_y2,e_y2/h^4\n";

  for (double h = step; h < 0.1; h += step) {
    errors = get_error(h);
    errors_h4_y1 = errors[0] / pow(h, 4);
    errors_h4_y2 = errors[1] / pow(h, 4);
    file << h << ',' << errors[0] << ',' << errors_h4_y1 << ',' << errors[1]
         << ',' << errors_h4_y2 << "\n";
  }
}