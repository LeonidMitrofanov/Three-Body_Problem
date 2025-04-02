#ifndef ODESOLVER_HPP
#define ODESOLVER_HPP

#include <functional>
#include <vector>

class ODESolver {
 public:
  ODESolver(const std::function<std::vector<double>(
                double, const std::vector<double>&)>& system,
            const std::vector<double>& initialConditions,
            double initialStepSize,
            const std::function<double(double, const std::vector<double>&,
                                       double)>& computeStep = nullptr);

  virtual void step(double x) = 0;
  std::vector<double> getState() const;
  double getStepSize() const;
  virtual ~ODESolver() = default;

 protected:
  std::function<std::vector<double>(double, const std::vector<double>&)>
      system_;             // Система ОДУ
  std::vector<double> y_;  // Текущее состояние системы
  double h_;               // Текущий шаг интегрирования
  std::function<double(double, const std::vector<double>&, double)>
      computeStep_;  // Функция для вычисления шага
};

// Класс для метода Рунге-Кутта 4-го порядка
class RungeKutta4 : public ODESolver {
 public:
  RungeKutta4(const std::function<std::vector<double>(
                  double, const std::vector<double>&)>& system,
              const std::vector<double>& initialConditions,
              double initialStepSize,
              const std::function<double(double, const std::vector<double>&,
                                         double)>& computeStep = nullptr);
  void step(double x) override;
};

#endif  // ODESOLVER_HPP