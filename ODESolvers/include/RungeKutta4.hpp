#include <algorithm>

#include "ASolver.hpp"

class RungeKutta4 : public ODESolver {
 public:
  using ODESolver::ODESolver;
  void make_step(double stepSize) override;
};