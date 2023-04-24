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
    std::vector<Solution> neighbors = GetNeighborhood(points);
    for (auto neighbor : neighbors) {
      if (neighbor.Value() > best_solution.Value()) {
        best_solution = neighbor;
      }
    }
    ++iterations;
  } while (best_solution.Value() > solution_.Value() && iterations < iterations_);
  return best_solution;
}