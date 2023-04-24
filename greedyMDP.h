#pragma once

#include "algorithm.h"

class GreedyMDP : public Algorithm {
 public:
  /**
   * @brief Constructor of the GreedyMDP class
   * 
   * @param points points of the problem
   */
  GreedyMDP(std::vector<Point> points, int number_of_points) : Algorithm(points, number_of_points) {}

  /**
   * @brief Solve the problem
   */
  void Solve() override;
};