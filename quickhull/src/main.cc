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
#include <vector>
#include <string>
#include <fstream>

#include "point_set.h"
#include "file_reader.h"

int main(int argc, char* argv[]) {
  Usage(argc, argv);
  std::ifstream input_points(argv[1]);
  bool d_option = false;
  if (argc == 3) {
    if (std::string(argv[2]) == "-d") {
      d_option = true;
    } else {
      std::cerr << "Wrong option, try --help for more information" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  std::vector<std::vector<std::string>> text_points = FileReader(input_points);
  std::vector<CyA::Point> points = TextToPoint(text_points);
  CyA::PointSet quickhull(points);
  quickhull.QuickHull();
  if (d_option) {
    std::string output_name = "output.dot";
    std::ofstream output_dot(output_name);
    if (output_dot.is_open()) {
      quickhull.WriteDot(output_dot);
      output_dot.close();
    } else {
      std::cerr << "Error opening file: " << output_name << std::endl;
    }
  } else {
    std::string output_name = "output.txt";
    std::ofstream output_txt(output_name);
    if (output_txt.is_open()) {
      quickhull.WriteHull(output_txt);
      output_txt.close();
    } else {
      std::cerr << "Error opening file: " << output_name << std::endl;
    }
  }
  return 0;
}

