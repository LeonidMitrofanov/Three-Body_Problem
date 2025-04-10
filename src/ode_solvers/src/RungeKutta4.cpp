#include "../include/ode_solvers.hpp"

void RungeKutta4::make_step(double stepSize) {
  const size_t n = currentState_.size();
  std::vector<double> k1(n), k2(n), k3(n), k4(n), temp(n);

  // Вычисление k1
  const auto& deriv1 = differentialEquation_(param_, currentState_);
  std::transform(deriv1.begin(), deriv1.end(), k1.begin(),
                 [stepSize](double val) { return stepSize * val; });

  // Вычисление k2
  std::transform(currentState_.begin(), currentState_.end(), k1.begin(),
                 temp.begin(),
                 [](double state, double k) { return state + 0.5 * k; });
  const auto& deriv2 = differentialEquation_(param_ + 0.5 * stepSize, temp);
  std::transform(deriv2.begin(), deriv2.end(), k2.begin(),
                 [stepSize](double val) { return stepSize * val; });

  // Вычисление k3
  std::transform(currentState_.begin(), currentState_.end(), k2.begin(),
                 temp.begin(),
                 [](double state, double k) { return state + 0.5 * k; });
  const auto& deriv3 = differentialEquation_(param_ + 0.5 * stepSize, temp);
  std::transform(deriv3.begin(), deriv3.end(), k3.begin(),
                 [stepSize](double val) { return stepSize * val; });

  // Вычисление k4
  std::transform(currentState_.begin(), currentState_.end(), k3.begin(),
                 temp.begin(),
                 [](double state, double k) { return state + k; });
  const auto& deriv4 = differentialEquation_(param_ + stepSize, temp);
  std::transform(deriv4.begin(), deriv4.end(), k4.begin(),
                 [stepSize](double val) { return stepSize * val; });

  // Обновление состояния
  for (size_t i = 0; i < n; ++i) {
    currentState_[i] += (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6.0;
  }

  param_ += stepSize;
}