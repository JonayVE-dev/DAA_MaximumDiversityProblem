#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "point.h"

class Problem {
 public:
  Problem() = default;
  Problem(std::string name);
  std::vector<Point>& GetPoints() { return points_; }

 private:
  std::vector<Point> points_; // points of the problem
};