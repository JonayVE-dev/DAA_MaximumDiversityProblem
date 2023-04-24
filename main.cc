#include <iostream>
#include <chrono>

#include "greedyMDP.h"
#include "graspMDP.h"

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
      int iterations = 100;
      int lrc_size = 3;
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
    } else if (algorithm == "???") {
       
    }
    file << labels << std::endl;
    file << line << std::endl;
    file.close();
}

int main() {
    srand(time(NULL));
    std::string input_file;
    std::cout << "Input file: ";
    std::cin >> input_file;
    std::string algorithm;
    std::cout << "Algorithm: ";
    std::cin >> algorithm;
    while (true) {
      int m = 5;
      std::cout << "M: ";
      std::cin >> m;
      printInformationToCSV(algorithm, input_file, m);

    }
    return 0;
}