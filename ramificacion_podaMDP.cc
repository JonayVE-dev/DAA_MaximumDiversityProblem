#include "ramificacion_podaMDP.h"

#include <algorithm>

struct Node {
  Solution solution;
  double upper_bound;
  bool operator<(Node& other) {
    return upper_bound < other.upper_bound;
  }
};

void PrintNodeSolution(Node node) {
  std::cout << "Solution: ";
  for (auto point : node.solution.GetPoints()) {
    std::cout << point.GetId() << " ";
  }
  std::cout << "Upper bound: " << node.upper_bound << std::endl;
}

double RamificacionPodaMDP::GetNodeSolutionValue(Solution node_solution) {
  int number_of_points = node_solution.GetPoints().size();
  std::vector<Point> solution_points = node_solution.GetPoints();
  int point_dimension = solution_points[0].GetDimension();
  // introduce puntos con id -1 en la solucion hasta que tenga el mismo numero de nodos que el problema
  while (number_of_points < number_of_points_) {
      std::vector<double> coordinates;
      for (int i = 0; i < point_dimension; i++) {
      coordinates.push_back(-1);
      }
      Point point(coordinates, -1);
      solution_points.push_back(point);
      number_of_points++;
  }
  
  double value = 0;
  // The value is the sum of the distances between all the points of the solution
  for (int i = 0; i < solution_points.size(); i++) {
    for (int j = i + 1; j < solution_points.size(); j++) {
      if (solution_points[i].GetId() != -1 && solution_points[j].GetId() != -1) {
        value += solution_points[i].Distance(solution_points[j]);
      } else {
        value += highest_distance_;
      }
    }
  }
  return value;
}




void RamificacionPodaMDP::HighValueSolver() {
  std::vector<Node> nodes;
  int number_of_points = initial_solution_.GetPoints().size();
  double best_solution_value_ = GetNodeSolutionValue(initial_solution_);
  Solution best_solution_ = initial_solution_;

  for (int i = 0; i < points_.size(); i++) {
    std::vector<Point> points;
    points.push_back(points_[i]);
    Solution solution(points);
    Node node;
    node.solution = solution;
    node.upper_bound = GetNodeSolutionValue(solution);
    nodes.push_back(node);
    ++nodes_generated_;
  }

  while (!nodes.empty()) {
    // Sort the nodes by upper bound
    std::sort(nodes.begin(), nodes.end());

    // Expandir el nodo con mayor cota superior
    Node node = nodes.back();
    nodes.pop_back();
    std::vector<Point> node_points = node.solution.GetPoints();
    int node_id = node_points.back().GetId();

    if (node_points.size() < number_of_points) {
      for (int i = node_id + 1; i < points_.size(); i++) {
        std::vector<Point> new_node_points = node_points;
        new_node_points.push_back(points_[i]);
        Solution new_node_solution(new_node_points);
        Node new_node;
        new_node.solution = new_node_solution;
        new_node.upper_bound = GetNodeSolutionValue(new_node_solution);
        nodes.push_back(new_node);
        ++nodes_generated_;
      }
    } else {
      if (GetNodeSolutionValue(node.solution) > best_solution_value_) {
        best_solution_value_ = GetNodeSolutionValue(node.solution);
        best_solution_ = node.solution;
      }
    }

    for (int nodo = 0; nodo < nodes.size(); nodo++) {
      if (nodes[nodo].solution.GetPoints().size() == number_of_points) {
        if (nodes[nodo].upper_bound < best_solution_value_) {
          nodes.erase(nodes.begin() + nodo);
          --nodo;
        }
      }
    }
  
  }
  solution_points_ = best_solution_;
}

void RamificacionPodaMDP::DeepSolver() {
  std::vector<Node> nodes;
  int number_of_points = initial_solution_.GetPoints().size();
  double best_solution_value_ = GetNodeSolutionValue(initial_solution_);
  Solution best_solution_ = initial_solution_;

  for (int i = 0; i < points_.size(); i++) {
    std::vector<Point> points;
    points.push_back(points_[i]);
    Solution solution(points);
    Node node;
    node.solution = solution;
    node.upper_bound = GetNodeSolutionValue(solution);
    nodes.push_back(node);
    ++nodes_generated_;
  }

  while (!nodes.empty()) {

    // Expandir el nodo con mayor cota superior
    Node node = nodes.back();
    nodes.pop_back();
    std::vector<Point> node_points = node.solution.GetPoints();
    int node_id = node_points.back().GetId();

    if (node_points.size() < number_of_points) {
      for (int i = node_id + 1; i < points_.size(); i++) {
        std::vector<Point> new_node_points = node_points;
        new_node_points.push_back(points_[i]);
        Solution new_node_solution(new_node_points);
        Node new_node;
        new_node.solution = new_node_solution;
        new_node.upper_bound = GetNodeSolutionValue(new_node_solution);
        nodes.push_back(new_node);
        ++nodes_generated_;
      }
    } else {
      if (GetNodeSolutionValue(node.solution) > best_solution_value_) {
        best_solution_value_ = GetNodeSolutionValue(node.solution);
        best_solution_ = node.solution;
      }
    }

    for (int nodo = 0; nodo < nodes.size(); nodo++) {
      if (nodes[nodo].solution.GetPoints().size() == number_of_points) {
        if (nodes[nodo].upper_bound < best_solution_value_) {
          nodes.erase(nodes.begin() + nodo);
          --nodo;
        }
      }
    }
  
  }
  solution_points_ = best_solution_;
}