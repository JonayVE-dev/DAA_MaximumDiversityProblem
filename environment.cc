#include "environment.h"

/**
 * @brief Local search method of an environment
 * @param points Points to calculate the error
 */
Solution Environment::LocalSearch(std::vector<Point> points) {
  int iterations = 0;
  Solution best_solution = solution_;
  do {
    solution_ = best_solution;
    double current_value = solution_.Value();
    std::vector<std::pair<Solution, double>> neighbors = GetNeighborhood(points);
    for (auto neighbor : neighbors) {
      double neighbor_value = neighbor.second;
      if (neighbor_value > current_value) {
        best_solution = neighbor.first;
      }
    }
    ++iterations;
  } while (best_solution.Value() > solution_.Value() && iterations < iterations_);
  return best_solution;
}