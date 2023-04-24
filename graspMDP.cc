#include "graspMDP.h"

Solution GraspMDP::Constructive() {
  // First, we calculate the gravity center point of the points and add the farthest point to the solution
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
    std::vector<Point> lrc(lrc_size_);
    gravity_center_point = GetGravityCenterPoint(solution_points);
    for (int j = 0; j < points_.size(); ++j) {
      if (std::find(solution_points.begin(), solution_points.end(), points_[j]) == solution_points.end()) {
        double distance = gravity_center_point.Distance(points_[j]);
        for (int k = 0; k < lrc.size(); ++k) {
          if (distance > lrc[k].Distance(gravity_center_point)) {
            lrc.insert(lrc.begin() + k, points_[j]);
            if (lrc.size() > lrc_size_) {
              lrc.pop_back();
            }
            break;
          }
        }
      }
    }
    int rand_index = rand() % lrc.size();
    solution_points.push_back(lrc[rand_index]);
  }
  return Solution(solution_points);
}

void GraspMDP::LocalSearch() {
  Solution constructive_solution = Constructive();
  Environment* environmnet = new ChangeEnvironment(iterations_);
  environmnet->ChangeSolution(constructive_solution);
  solution_points_ = environmnet->LocalSearch(points_); 
}

void GraspMDP::Solve() {
  LocalSearch();
}