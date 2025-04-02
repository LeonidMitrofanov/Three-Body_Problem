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

int main() {
  const char orbit_path[] = "../data/three_body_orbit.csv";
  vector<double> y_three_body = {0.994, 0.0, 0.0, -2.031732629557337};
  double t_three_body = 0.0;
  double T_three_body = 11.124340337;
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
  RungeKutta4 solver_three_body(threeBodySystem, y_three_body, h_initial,
                                computeStepThreeBody);

  ofstream file_three_body(orbit_path);
  file_three_body << "t,x,y,vx,vy\n";

  while (t_three_body < T_three_body) {
    file_three_body << t_three_body << "," << y_three_body[0] << ","
                    << y_three_body[1] << "," << y_three_body[2] << ","
                    << y_three_body[3] << "\n";

    solver_three_body.step(t_three_body);
    y_three_body = solver_three_body.getState();
    t_three_body += solver_three_body.getStepSize();
  }

  file_three_body.close();
  cout << "Данные сохранены в " << orbit_path << endl;

  return 0;
}