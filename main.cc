#include <iostream>
#include <chrono>

#include "greedyMDP.h"
#include "graspMDP.h"
#include "ramificacion_podaMDP.h"

/**
 * @brief Print the information of the execution to a csv file
 * @param algorithm Algorithm used
 * @param input_file Input file used
 */
void printInformationToCSV(std::string algorithm, std::string input_file, int m) {
    std::ofstream file;
    std::string line;
    file.open("./results.csv", std::ios::app);
    std::string labels = "Problema,n,K,m,z,S,CPU";
    Problem problem("./problems/" + input_file);
    std::vector<Point> points;
    points.push_back(problem.GetPoints()[0]);
    if (algorithm == "greedy") {
      GreedyMDP greedyMDP(problem.GetPoints(), m);
      auto start = std::chrono::high_resolution_clock::now();
      greedyMDP.Solve();
      auto end = std::chrono::high_resolution_clock::now();
      // give the time in seconds
      auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

      line += input_file + "," + std::to_string(problem.GetPoints().size()) + "," + std::to_string(problem.GetPoints()[0].GetDimension()) 
      + "," + std::to_string(m) + "," + std::to_string(greedyMDP.GetSolution().Value()) + "," + greedyMDP.GetSolution().ToString()
      + "," + std::to_string(elapsed_seconds.count());
      std::cout << greedyMDP.GetSolution().ToString() << std::endl;
      std::cout << greedyMDP.GetSolution().Value() << std::endl;
    } else if (algorithm == "grasp") {
      int iterations;
      std::cout << "Introduce the number of iterations: ";
      std::cin >> iterations;
      int lrc_size;
      std::cout << "Introduce the size of the LRC: ";
      std::cin >> lrc_size;
      labels += ",Iter,|LRC|";
      GraspMDP graspMDP(problem.GetPoints(), m, lrc_size, iterations);
      auto start = std::chrono::high_resolution_clock::now();
      graspMDP.Solve();
      auto end = std::chrono::high_resolution_clock::now();
      // give the time in seconds
      auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

      line += input_file + "," + std::to_string(problem.GetPoints().size()) + "," + std::to_string(problem.GetPoints()[0].GetDimension())
      + "," + std::to_string(m) + "," + std::to_string(graspMDP.GetSolution().Value()) + "," + graspMDP.GetSolution().ToString()
      + "," + std::to_string(elapsed_seconds.count()) + "," + std::to_string(iterations) + "," + std::to_string(lrc_size);
      std::cout << graspMDP.GetSolution().ToString() << std::endl;
      std::cout << graspMDP.GetSolution().Value() << std::endl;
    } else if (algorithm == "poda") {
      labels += ",nodos generados";
      std::cout << "poda" << std::endl;
      std::cout << "Search strategy: " << std::endl;
      std::cout << "1. high_value" << std::endl;
      std::cout << "2. deep_search" << std::endl;
      int search_strategy_number;
      std::cin >> search_strategy_number;
      std::string search_strategy = (search_strategy_number == 1) ? "high_value" : "deep_search";
      std::cout << "Initial solution strategy: " << std::endl;
      std::cout << "1. greedy" << std::endl;
      std::cout << "2. grasp" << std::endl;
      int initial_solution_strategy_number;
      std::cin >> initial_solution_strategy_number;
      std::string initial_solution_strategy = (initial_solution_strategy_number == 1) ? "greedy" : "grasp";
      labels += ",Estrategia de busqueda,Estrategia de solucion inicial";
      RamificacionPodaMDP ramificacionPodaMDP(problem.GetPoints(), m, search_strategy, initial_solution_strategy);
      auto start = std::chrono::high_resolution_clock::now();
      ramificacionPodaMDP.Solve();
      auto end = std::chrono::high_resolution_clock::now();
      // give the time in seconds
      auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
      std::string nodos_generados = std::to_string(ramificacionPodaMDP.GetNodesGenerated());
      line += input_file + "," + std::to_string(problem.GetPoints().size()) + "," + std::to_string(problem.GetPoints()[0].GetDimension())
      + "," + std::to_string(m) + "," + std::to_string(ramificacionPodaMDP.GetSolution().Value()) + "," + ramificacionPodaMDP.GetSolution().ToString()
      + "," + std::to_string(elapsed_seconds.count()) + "," + nodos_generados;
      std::cout << ramificacionPodaMDP.GetSolution().ToString() << std::endl;
      std::cout << ramificacionPodaMDP.GetSolution().Value() << std::endl;
      std::cout << "Nodos generados: " << nodos_generados << std::endl;
       
    }
    file << labels << std::endl;
    file << line << std::endl;
    file.close();
}

int main() {
    srand(time(NULL));
    std::string algorithm;
    std::cout << "Algorithm: ";
    std::cin >> algorithm;
      std::string input_file;
      std::cout << "Input file: ";
      std::cin >> input_file;
      for (int j = 2; j <= 5; j++) {
        printInformationToCSV(algorithm, input_file, j);
      }
    return 0;
}