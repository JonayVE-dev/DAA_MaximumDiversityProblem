#include "point.h"

#include <cmath>
#include <iostream>

/**
 * @brief Calculate the distance between two points
 * 
 * @param other Other point
 * @return The distance between the two points
 */
double Point::Distance(const Point& other) const {
  double sum = 0;
  for (int i = 0; i < dimension_; i++) {
    sum += pow(coordinates_[i] - other.coordinates_[i], 2);
  }
  return sqrt(sum);
}

/**
 * @brief Calculate the distance between a point and a vector of points
 * 
 * @param centroids Vector of points
 * @return The distance between the point and the vector of points
 */
double Point::Distance(const std::vector<Point>& centroids) const {
  double min_distance = Distance(centroids[0]);
  for (int i = 1; i < centroids.size(); i++) {
    double distance = Distance(centroids[i]);
    if (distance < min_distance) {
      min_distance = distance;
    }
  }
  return min_distance;
}

/**
 * @brief Get the dimension of the point
 * 
 * @return The dimension of the point
 */
std::string Point::ToString() const {
  std::string result;
  for (int i = 0; i < coordinates_.size(); i++) {
    result += std::to_string(coordinates_[i]) + " ";
  }
  result.pop_back();
  return result;
}

bool Point::operator==(const Point& other) const {
  if (dimension_ == other.dimension_ && id_ == other.id_) {
    return true;
  }
  return false;
}