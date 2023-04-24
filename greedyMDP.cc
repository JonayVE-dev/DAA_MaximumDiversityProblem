#include "greedyMDP.h"

void GreedyMDP::Solve() {
  // First, we calculate the gravity center point of the points and add the nearest point to the solution
  Point gravity_center_point = GetGravityCenterPoint(points_);
  std::vector<Point> solution_points;
  double max_distance = std::numeric_limits<double>::min();
  int max_distance_point_index = -1;
  for (int i = 0; i < points_.size(); ++i) {
    double distance = gravity_center_point.Distance(points_[i]);
    if (distance > max_distance) {
      max_distance = distance;
      max_distance_point_index = i;
    }
  }
  solution_points.push_back(points_[max_distance_point_index]);

  max_distance = std::numeric_limits<double>::min();
  max_distance_point_index = -1;

  for (int i = 1; i < number_of_points_; ++i) {
    gravity_center_point = GetGravityCenterPoint(solution_points);
    max_distance = std::numeric_limits<double>::min();
    max_distance_point_index = -1;
    for (int j = 0; j < points_.size(); ++j) {
      if (std::find(solution_points.begin(), solution_points.end(), points_[j]) == solution_points.end()) {
        double distance = gravity_center_point.Distance(points_[j]);
        if (distance > max_distance) {
          max_distance = distance;
          max_distance_point_index = j;
        }
      }
    }
    solution_points.push_back(points_[max_distance_point_index]);
  }
  solution_points_ = Solution(solution_points);
}