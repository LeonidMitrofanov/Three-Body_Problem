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

  double m = 0.012277471;  // Масса Луны
  double M = 1 - m;        // Масса Земли

  double R1 = pow((x + m) * (x + m) + y_pos * y_pos, 1.5);
  double R2 = pow((x - M) * (x - M) + y_pos * y_pos, 1.5);

  double dxdt = vx;
  double dydt = vy;
  double dvxdt = x + 2 * vy - (M / R1) * (x + m) - m * (x - M) / R2;
  double dvydt = y_pos - 2 * vx - (M / R1) * y_pos - m * y_pos / R2;

  return {dxdt, dydt, dvxdt, dvydt};
}

int main() {
  const char orbit_path[] = "../data/three_body_orbit.csv";
  vector<double> y_three_body = {
      0.994, 0.0, 0.0,
      -2.031732629557337};  // Начальные условия для задачи трёх тел
  double t_three_body = 0.0;
  double T_three_body = 11.124340337;  // Период орбиты Аренстора
  double h_three_body = 1e-4;          // Шаг интегрирования

  // Создаём решатель для задачи трёх тел
  RungeKutta4 solver_three_body(threeBodySystem, y_three_body, h_three_body);

  // Открываем файл для сохранения траектории
  ofstream file_three_body(orbit_path);
  file_three_body << "t,x,y,vx,vy\n";

  // Интегрируем уравнения до времени T_three_body
  while (t_three_body < T_three_body) {
    file_three_body << t_three_body << "," << y_three_body[0] << ","
                    << y_three_body[1] << "," << y_three_body[2] << ","
                    << y_three_body[3] << "\n";

    solver_three_body.step(t_three_body);
    y_three_body = solver_three_body.getState();
    t_three_body += solver_three_body.getStepSize();
  }

  file_three_body.close();
  cout << "Задача трёх тел: Данные сохранены в " << orbit_path << endl;

  return 0;
}