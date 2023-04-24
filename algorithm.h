#pragma once
#include <algorithm>

#include "problem.h"
#include "solution.h"
#include "point.h"

class Algorithm {
 public:
  /**
   * @brief Constructor of the algorithm class
   * 
   * @param points points of the problem
   */
  Algorithm(std::vector<Point> points, int number_of_points) : points_(points), number_of_points_(number_of_points) {}

  /**
   * @brief Solve the problem
   */
  virtual void Solve() = 0;

  /**
   * @brief Get the Solution object
   */
  Solution GetSolution() { return solution_points_; }

  /**
   * @brief Get the Gravity Center Point of a vector of points
   * @param points vector of points
   * @return Point gravity center point
   */
  Point GetGravityCenterPoint(std::vector<Point> points) {
    int dimension = points[0].GetDimension();
    std::vector<double> gravity_center_point_coordinates(dimension, 0.0);
    for (auto point : points) {
      for (int i = 0; i < dimension; i++) {
        gravity_center_point_coordinates[i] += point.GetCoordinates()[i];
      }
    }
    for (int i = 0; i < dimension; i++) {
      gravity_center_point_coordinates[i] /= points.size();
    }
    return Point(gravity_center_point_coordinates, -1);
  }

 protected:
  int number_of_points_; // number of points of the problem
  std::vector<Point> points_; // points of the problem
  Solution solution_points_; // clusters of the solution
};