#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "../ODESolver/include/ODESolvers.hpp"

using namespace std;

vector<double> threeBodySystem(double t, const vector<double>& y) {
  double x = y[0];
  double y_pos = y[1];
  double vx = y[2];
  double vy = y[3];

  double m = 0.012277471;
  double M = 1 - m;

  double R1 = pow((x + m) * (x + m) + y_pos * y_pos, 1.5);
  double R2 = pow((x - M) * (x - M) + y_pos * y_pos, 1.5);

  double ax = x + 2 * vy - (M / R1) * (x + m) - m * (x - M) / R2;
  double ay = y_pos - 2 * vx - (M / R1) * y_pos - m * y_pos / R2;

  return {vx, vy, ax, ay};
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <output_path>" << endl;
    return 1;
  }

  const string path = argv[1];
  vector<double> y = {0.994, 0.0, 0.0, -2.031732629557337};
  double t = 0.0;
  double T = 11.124340337;
  double h_initial = 1e-4;

  // Функция для вычисления адаптивного шага
  double m = 0.012277471;
  double M = 1 - m;
  auto computeStepThreeBody = [m, M](double x, const vector<double>& y,
                                     double h_prev) {
    double x_pos = y[0];
    double y_pos = y[1];

    // Вычисляем расстояния
    double R1 = sqrt(pow(x_pos + m, 2) + pow(y_pos, 2));
    double R2 = sqrt(pow(x_pos - M, 2) + pow(y_pos, 2));

    // Линейная зависимость шага от минимального расстояния
    double k = 1e-3;  // Коэффициент подбирается экспериментально
    double h_new = k * min(R1, R2);

    // Ограничиваем шаг диапазоном [h_min, h_max]
    double h_min = 1e-6;
    double h_max = 1e-2;
    return clamp(h_new, h_min, h_max);
  };

  // Создаём решатель с адаптивным шагом
  RungeKutta4 solver(threeBodySystem, y, h_initial, computeStepThreeBody);

  ofstream file(path);
  file << "t,x,y,vx,vy\n";

  while (t < T) {
    file << t << "," << y[0] << "," << y[1] << "," << y[2] << "," << y[3]
         << "\n";

    solver.step(t);
    y = solver.getState();
    t += solver.getStepSize();
  }

  file.close();
  return 0;
}