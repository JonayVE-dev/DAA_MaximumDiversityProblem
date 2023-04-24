#pragma once
#include <fstream>
#include <string>
#include "point.h"

class Solution {
 public:
  Solution() {}
  Solution(std::vector<Point> point) : solution_points_(point) {}
  std::vector<Point> GetPoints() { return solution_points_; }
  double Value();
  std::string ToString();
 private:
  std::vector<Point> solution_points_; // points of the solution
};