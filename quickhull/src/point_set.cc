// Universidad de La Laguna
// Escuela Superior de Ingenieríıa y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 12: Algoritmo Divide y Vencerás
// Autor: José Ángel Portillo García
// Correo: alu0101568232@ull.edu.es
// Fecha: 12/12/2023

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <limits>

#include "point_set.h"

void CyA::PointSet::QuickHull(void) {
  hull_.clear();
  CyA::Point min_x_point; 
  CyA::Point max_x_point;
  XBounds(min_x_point, max_x_point);
  QuickHull(CyA::Line(min_x_point, max_x_point), side::LEFT);
  QuickHull(CyA::Line(min_x_point, max_x_point), side::RIGHT);
  // Remove duplicates
  std::sort(hull_.begin(), hull_.end());
  hull_.erase(std::unique(hull_.begin(), hull_.end()), hull_.end());
}


void CyA::PointSet::QuickHull(const CyA::Line &line, int side) {
  CyA::Point farthest;
  if (FarthestPoint(line, side, farthest)) {
    QuickHull(CyA::Line(line.first, farthest), -FindSide(CyA::Line(line.first, farthest), line.second));
    QuickHull(CyA::Line(farthest, line.second), -FindSide(CyA::Line(farthest, line.second), line.first));
  } else {
      hull_.push_back(line.first);
      hull_.push_back(line.second);
    }
}


bool CyA::PointSet::FarthestPoint(const CyA::Line &line, int side, CyA::Point &farthest) const {
  farthest = points_.at(0);
  double max_dist = 0;
  bool found = false;
  for (const CyA::Point &point : points_) {
    const double dist = Distance(line, point);
    if (FindSide(line, point) == side && dist > max_dist) {
      farthest = point;
      max_dist = dist;
      found = true;
    }
  }
  return found;
}


double CyA::PointSet::PointToLine(const CyA::Line &line, const CyA::Point &point) const {
  const CyA::Point &point_1 = line.first;
  const CyA::Point &point_2 = line.second;
  return (point.second - point_1.second) * (point_2.first - point_1.first) -
         (point_2.second - point_1.second) * (point.first - point_1.first);
}


double CyA::PointSet::Distance(const CyA::Line &line, const CyA::Point &point) const {
  return fabs(PointToLine(line, point));
}


void CyA::PointSet::WriteHull(std::ostream &os) const {
  for(const auto& point : hull_) {
    os << "(" << point.first << ", " << point.second << ")\n";
  }
  os.flush();
}


void CyA::PointSet::WriteDot(std::ostream &os) const {
  os << " graph { \n \n";
  std::map<CyA::Point, int> point_ids;
  int i = 0;
  for (const auto& point : points_) {
    os << i << "[pos=\"" << point.first << "," << point.second << "!\"]\n";
    point_ids.emplace(point, i);
    i++;
  }
  os << "\n";
  
  for (int i = 0, j = i + 1; i < hull_.size() - 1; i++) {
    double distance = 0;
    double min_distance = std::numeric_limits<double>::infinity();
    CyA::Point point_1;
    CyA::Point point_2;
    for(int j = i + 1; j < hull_.size(); j++) {
      distance = PointToPoint(hull_[i], hull_[j]);
      if (min_distance > distance) {
        min_distance = distance;
        point_1 = hull_[i];
        point_2 = hull_[j];
      }
    }
    os << point_ids.at(point_1) << " -- " << point_ids.at(point_2) << "\n";
  }
    double distance = 0;
    double max_distance = 0;
    CyA::Point point_1;
    CyA::Point point_2;
  for (int i = 0; i < hull_.size() - 1; i++) {
    distance = PointToPoint(hull_[hull_.size() - 1], hull_[i]);
    if (max_distance < distance) {
      max_distance = distance;
      point_1 = hull_[hull_.size() - 1];
      point_2 = hull_[i];
    }
  }
  os << point_ids.at(point_1) << " -- " << point_ids.at(point_2) << "\n";
  os << "}\n";
  os.flush();
}


double CyA::PointSet::PointToPoint(const CyA::Point& point1, const CyA::Point& point2) const {
  return sqrt((pow(point2.first - point1.first, 2)) + (pow(point2.second - point1.second, 2)));
}


void CyA::PointSet::XBounds(Point &min_x, Point &max_x) const {
  double distance = 0;
  double max_distance = 0;
  for (int i = 0; i < points_.size() - 1; i++) {
    CyA::Point point_1 = points_[i];
    for (int j = i + 1; j < points_.size(); j++) {
      CyA::Point point_2 = points_[j];
      distance = PointToPoint(point_1, point_2);
      if (distance > max_distance) {
        max_distance = distance;
        min_x = point_1;
        max_x = point_2;
      }
    }
  }
}


int CyA::PointSet::FindSide(const Line &line, const Point &point) const {
  double val = (point.second - line.first.second) * (line.second.first - line.first.first) -
               (line.second.second - line.first.second) * (point.first - line.first.first);
  if (val > 0)
    return CyA::side::RIGHT;
  else if (val < 0)
    return CyA::side::LEFT;
  else
    return CyA::side::CENTER;
}
