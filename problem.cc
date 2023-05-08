#include "problem.h"

/**
 * @brief Construct a new Problem:: Problem object
 * @param name Name of the file with the problem
 */
Problem::Problem(std::string name) {
  std::ifstream file(name);
  std::string line;
  std::getline(file, line);
  int number_of_points = std::stoi(line);
  std::getline(file, line);
  int dimension = std::stoi(line);
  int id = 0;
  while (std::getline(file, line)) {
    std::vector<double> coordinates(dimension);
    std::stringstream ss(line);
    for (int i = 0; i < dimension; i++) {
      ss >> coordinates[i];
    }
    points_.push_back(Point(coordinates, id));
    id++;
  }
}