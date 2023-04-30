#include "change_environment.h"

/**
 * @brief Get the neighbord solution of the current solution
 * 
 * @param points Points of the problem
 * @return A vector of solutions
 */

std::vector<std::pair<Solution, double>> ChangeEnvironment::GetNeighborhood(std::vector<Point> points) {
  std::vector<std::pair<Solution, double>> neighborhood;
  double current_value = solution_.Value();
  for (int i = 0; i < solution_.GetPoints().size(); ++i) {
    for (int j = 0; j < points.size(); ++j) {
      if (solution_.GetPoints()[i].GetId() != points[j].GetId()) {
        std::vector<Point> new_solution = solution_.GetPoints();
        new_solution[i] = points[j];
        double new_value = current_value;
        for (int k = 0; k < new_solution.size(); ++k) {
          if (k != i) {
            new_value += new_solution[i].Distance(new_solution[k]);
            new_value -= solution_.GetPoints()[i].Distance(solution_.GetPoints()[k]);
          }
        }
        std::cout << "New value: " << new_value << std::endl;
        std::cout << "New value using value function: " << Solution(new_solution).Value() << std::endl << std::endl;
        neighborhood.push_back(std::pair<Solution, int>(Solution(new_solution), new_value));
      }
    }
  }
  return neighborhood;
}