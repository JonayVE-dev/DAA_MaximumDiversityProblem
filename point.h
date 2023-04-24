#pragma once

#include <iostream>
#include <string>
#include <vector>

class Point {
 public:
  Point() = default;
  Point(std::vector<double> coordinates, int id) : coordinates_(coordinates), id_(id) {
    dimension_ = coordinates_.size();
  }
  double Distance(const Point& other) const;
  double Distance(const std::vector<Point>& centroids) const;
  int GetDimension() const { return dimension_; }
  std::vector<double> GetCoordinates() const { return coordinates_; }
  std::string ToString() const;
  int GetId() const { return id_; }
  bool operator==(const Point& other) const;

 private:
  std::vector<double> coordinates_; // coordinates of the point
  int dimension_;                  // dimension of the point
  int id_;                         // id of the point
};