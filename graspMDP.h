#pragma once

#include "algorithm.h"
#include "change_environment.h"

class GraspMDP : public Algorithm {
 public:
  /**
   * @brief Constructor of the grasp algorithm class
   * 
   * @param points points of the problem
   * @param number_of_iterations number of iterations of the algorithm
   * @param number_of_points number of points of the problem
   */
  GraspMDP(std::vector<Point> points, int number_of_points, int lrc_size, int iterations) : Algorithm(points, number_of_points), lrc_size_(lrc_size), iterations_(iterations) {}

  /**
   * @brief Solve the problem
   */
  void Solve();

  /**
   * @brief Constructive phase of the algorithm
   */
  Solution Constructive();

  /**
   * @brief Local search phase of the algorithm
   */
  void LocalSearch();

 private:
  int lrc_size_; // size of the local restricted candidate list
  int iterations_; // number of iterations of the algorithm
};