#ifndef ODESOLVER_HPP
#define ODESOLVER_HPP

#include <vector>
#include <functional>

class ODESolver {
public:
    // Конструктор
    ODESolver(const std::function<std::vector<double>(double, const std::vector<double>&)>& system,
              const std::vector<double>& initialConditions, double initialStepSize,
              const std::function<double(double, const std::vector<double>&, double)>& computeStep = nullptr);

    // Виртуальный метод для выполнения одного шага интегрирования
    virtual void step(double x) = 0;

    // Метод для получения текущего состояния системы
    std::vector<double> getState() const;

    // Метод для получения текущего шага
    double getStepSize() const;

    // Виртуальный деструктор
    virtual ~ODESolver() = default;

protected:
    std::function<std::vector<double>(double, const std::vector<double>&)> system_; // Система ОДУ
    std::vector<double> y_; // Текущее состояние системы
    double h_; // Текущий шаг интегрирования
    std::function<double(double, const std::vector<double>&, double)> computeStep_; // Функция для вычисления шага
};

// Класс для метода Рунге-Кутта 4-го порядка
class RungeKutta4 : public ODESolver {
public:
    // Конструктор
    RungeKutta4(const std::function<std::vector<double>(double, const std::vector<double>&)>& system,
                const std::vector<double>& initialConditions, double initialStepSize,
                const std::function<double(double, const std::vector<double>&, double)>& computeStep = nullptr);

    // Реализация метода step для Рунге-Кутта 4-го порядка
    void step(double x) override;
};

#endif // ODESOLVER_HPP