#include "change_environment.h"

/**
 * @brief Get the neighbord solution of the current solution
 * 
 * @param points Points of the problem
 * @return A vector of solutions
 */
std::vector<Solution> ChangeEnvironment::GetNeighborhood(std::vector<Point> points) {
  std::vector<Solution> neighborhood;
  for (int i = 0; i < solution_.GetPoints().size(); ++i) {
    for (int j = 0; j < points.size(); ++j) {
      if (solution_.GetPoints()[i].GetId() != points[j].GetId()) {
        std::vector<Point> new_centroids = solution_.GetPoints();
        new_centroids[i] = points[j];
        neighborhood.push_back(Solution(new_centroids));
      }
    }
  }
  return neighborhood;
}