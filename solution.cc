#include "solution.h"

double Solution::Value() {
  double value = 0;
  // The value is the sum of the distances between all the points of the solution
  for (int i = 0; i < solution_points_.size(); i++) {
    for (int j = i + 1; j < solution_points_.size(); j++) {
      value += solution_points_[i].Distance(solution_points_[j]);
    }
  }
  return value;
}

std::string Solution::ToString() {
  std::string solution_string = "";
  for (int i = 0; i < solution_points_.size(); i++) {
    solution_string += std::to_string(solution_points_[i].GetId());
    if (i != solution_points_.size() - 1) {
      solution_string += " ";
    }
  }
  return solution_string;
}