#pragma once
#include "solution.h"

class Environment {
 public:
  Environment(int iterations = 1000) : iterations_(iterations) {}
  virtual std::vector<std::pair<Solution, double>> GetNeighborhood(std::vector<Point> points) = 0;
  void ChangeSolution(Solution solution) { solution_ = solution;}
  Solution LocalSearch(std::vector<Point> points);
 protected:
  Solution solution_; // Current solution
  int iterations_; // Number of iterations
};