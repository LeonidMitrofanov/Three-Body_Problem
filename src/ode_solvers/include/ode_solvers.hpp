#ifndef ODESOLVER_HPP
#define ODESOLVER_HPP

#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

using ODE = function<vector<double>(double, const vector<double>&)>;

class ODESolver {
 public:
  ODESolver(ODE differentialEquation, const vector<double>& initialState,
            double initialParam = 0)
      : differentialEquation_(differentialEquation),
        currentState_(initialState),
        param_(initialParam) {}
  virtual ~ODESolver() = default;
  virtual void make_step(double stepSize) = 0;
  const double getParam() const { return param_; }
  const vector<double>& getState() const { return currentState_; }

 protected:
  ODE differentialEquation_;
  vector<double> currentState_;
  double param_;
};

class RungeKutta4 : public ODESolver {
 public:
  using ODESolver::ODESolver;
  void make_step(double stepSize) override;
};

#endif  // ODESOLVER_HPP