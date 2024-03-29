#pragma once

#include "environment.h"

class ChangeEnvironment : public Environment {
 public:
  ChangeEnvironment(int iterations = 1000) : Environment(iterations) {}
  std::vector<std::pair<Solution, double>> GetNeighborhood(std::vector<Point> points);
};