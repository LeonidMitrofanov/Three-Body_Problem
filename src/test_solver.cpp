#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "../ODESolver/include/ODESolvers.hpp"

using namespace std;

vector<double> testSystem(double t, const vector<double>& y) {
  double y1 = y[0];
  double y2 = y[1];

  double dy1dt = -y2 + y1 * (y1 * y1 + y2 * y2 - 1);
  double dy2dt = y1 + y2 * (y1 * y1 + y2 * y2 - 1);

  return {dy1dt, dy2dt};
}

int main() {
  const char test_path[] = "../data/test.csv";
  vector<double> y_test = {1.0 / sqrt(2),
                           0.0};  // Начальные условия для тестовой задачи
  double t_test = 0.0;
  double T_test = 5.0;  // Конечное время для тестовой задачи
  double h_test = 0.01;  // Шаг интегрирования

  // Создаём решатель для тестовой задачи
  RungeKutta4 solver_test(testSystem, y_test, h_test);

  // Открываем файл для сохранения траектории
  ofstream file_test(test_path);
  file_test << "t,y1,y2\n";

  // Интегрируем уравнения до времени T_test
  while (t_test < T_test) {
    file_test << t_test << "," << y_test[0] << "," << y_test[1] << "\n";

    solver_test.step(t_test);
    y_test = solver_test.getState();
    t_test += solver_test.getStepSize();
  }

  file_test.close();
  cout << "Тестовая задача: Данные сохранены в " << test_path << endl;

  return 0;
}