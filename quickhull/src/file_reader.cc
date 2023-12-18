// Universidad de La Laguna
// Escuela Superior de Ingenieríıa y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 12: Algoritmo Divide y Vencerás
// Autor: José Ángel Portillo García
// Correo: alu0101568232@ull.edu.es
// Fecha: 12/12/2023

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <sstream>

#include "file_reader.h"
#include "point_set.h"

const std::string kTitle = "P011-Greedy-Algorithm";
const std::string kHelpText =
"  \n\033[1m>> Example:\033[0m"\
"    ./a.out input.txt -d\n"\
  
"  \033[1m>> Parameters:\033[0m\n"\
"     - \033[1minput.txt:\033[0m is the file with the points to be input\n"\
"     - \033[1m-d:\033[0m is an option to generate a file in graphviz format\n"\
  
"  \033[1m>> Output:\033[0m\n"\
"    The program will output the result of an Quickhull Algorithm"\
" of the input points.\n";

/**
 * @brief The function usage of the program that deals with the parameters
 * 
 * @param argc 
 * @param argv 
 */
void Usage(int argc, char* argv[]) {
  const std::string kHelp = "--help";
  if (argc == 1) {
    std::cerr << argv[0] << std::endl << kTitle << std::endl;
    std::cerr << "How to use: " << argv[0]
              << " input.txt -d"
              << std::endl;
    std::cerr << "Try " << argv[0] << " --help for more information."
              << std::endl;
    exit(EXIT_FAILURE);
  }
  if (argv[1] == kHelp) {
    std::cout << kTitle << std::endl;
    std::cout << kHelpText << std::endl;
    exit(EXIT_SUCCESS);
  }
  if ((argc > 3) || ((argc < 2))) {
    std::cerr << argv[0] << std::endl << kTitle << std::endl;
    std::cerr << "How to use: " << argv[0]
              << " input.txt -d"
              << std::endl;
    std::cerr << "Try " << argv[0] << " --help for more information."
              << std::endl;
    exit(EXIT_FAILURE);
  }
}


/**
 * @brief The function will receive a ifstream file and convert it to a vector of vectors of strings
 * 
 * @param input_files 
 * @return std::vector<std::vector<std::string>> 
 */
std::vector<std::vector<std::string>> FileReader(std::ifstream& input_files) {
  std::vector<std::vector<std::string>> result;
  std::string line;
  while (std::getline(input_files, line)) {
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
      tokens.push_back(token);
    }
    result.push_back(tokens);
  }
  input_files.close();
  return result;
}


/**
 * @brief The function will convert a vector of vectors of strings, to a vector of points
 * 
 * @param text_point 
 * @return CyA::PointVector 
 */
std::vector<CyA::Point> TextToPoint(const std::vector<std::vector<std::string>>& text_point) {
  std::vector<CyA::Point> points;
  int point_amount = stoi(text_point[0][0]);
  for (int i = 1; i < text_point.size(); i++) {
    points.emplace_back(std::make_pair(std::stod(text_point[i][0]), std::stod(text_point[i][1])));
  }
  if(points.size() < point_amount) {
    std::cerr << "The input points are less than expected" << std::endl;
    exit(EXIT_FAILURE);
  } else if (points.size() > (point_amount)) {
    std::cerr << "The input points are more than expected" << std::endl;
    exit(EXIT_FAILURE);
  } else {
    return points;
  }
}
