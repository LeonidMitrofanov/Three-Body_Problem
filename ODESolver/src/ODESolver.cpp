#include "../include/ODESolvers.hpp"

// Конструктор ODESolver
ODESolver::ODESolver(const std::function<std::vector<double>(double, const std::vector<double>&)>& system,
                     const std::vector<double>& initialConditions, double initialStepSize,
                     const std::function<double(double, const std::vector<double>&, double)>& computeStep)
    : system_(system), y_(initialConditions), h_(initialStepSize) {
        if (computeStep) {
            computeStep_ = computeStep;
        } else {
            // По умолчанию фиксированный шаг
            computeStep_ = [](double x, const std::vector<double>& y, double h) { return h; };
        }
    }

// Метод для получения текущего состояния системы
std::vector<double> ODESolver::getState() const {
    return y_;
}

// Метод для получения текущего шага
double ODESolver::getStepSize() const {
    return h_;
}

// Конструктор RungeKutta4
RungeKutta4::RungeKutta4(const std::function<std::vector<double>(double, const std::vector<double>&)>& system,
                         const std::vector<double>& initialConditions, double initialStepSize,
                         const std::function<double(double, const std::vector<double>&, double)>& computeStep)
    : ODESolver(system, initialConditions, initialStepSize, computeStep) {}

// Реализация метода step для Рунге-Кутта 4-го порядка
void RungeKutta4::step(double x) {
    size_t n = y_.size();
    std::vector<double> k1(n), k2(n), k3(n), k4(n), dydx(n), y_temp(n);

    // Вычисление k1
    dydx = system_(x, y_);
    for (size_t i = 0; i < n; ++i) {
        k1[i] = h_ * dydx[i];
        y_temp[i] = y_[i] + 0.5 * k1[i];
    }

    // Вычисление k2
    dydx = system_(x + 0.5 * h_, y_temp);
    for (size_t i = 0; i < n; ++i) {
        k2[i] = h_ * dydx[i];
        y_temp[i] = y_[i] + 0.5 * k2[i];
    }

    // Вычисление k3
    dydx = system_(x + 0.5 * h_, y_temp);
    for (size_t i = 0; i < n; ++i) {
        k3[i] = h_ * dydx[i];
        y_temp[i] = y_[i] + k3[i];
    }

    // Вычисление k4
    dydx = system_(x + h_, y_temp);
    for (size_t i = 0; i < n; ++i) {
        k4[i] = h_ * dydx[i];
        y_[i] += (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6.0;
    }

    // Адаптивное изменение шага
    h_ = computeStep_(x, y_, h_);
}