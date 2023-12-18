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

void Usage(int argc, char* argv[]);
std::vector<std::vector<std::string>> FileReader(std::ifstream& input_files);
std::vector<CyA::Point> TextToPoint(const std::vector<std::vector<std::string>>& text_point);
