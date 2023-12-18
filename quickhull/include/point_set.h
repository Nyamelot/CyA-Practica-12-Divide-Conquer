// Universidad de La Laguna
// Escuela Superior de Ingenieríıa y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 12: Algoritmo Divide y Vencerás
// Autor: José Ángel Portillo García
// Correo: alu0101568232@ull.edu.es
// Fecha: 12/12/2023

#ifndef POINT_SET_H_
#define POINT_SET_H_

#include <iostream>
#include <vector>

namespace CyA {
  using Point = std::pair<double,double>;
  using Line = std::pair<Point, Point>;
  using PointVector = std::vector<Point>;

  enum side {
    LEFT = -1,
    CENTER,
    RIGHT
  };
 
  class PointSet : public PointVector {
   public:
    // Constructor
    PointSet(const vector<Point> &points) : points_(points) {}

    // Methods 
    void QuickHull(void); 
    void WriteHull(std::ostream &os) const;
    void WriteDot(std::ostream &os) const;

    // Getters
    inline const PointVector& GetHull(void) const { return hull_; }
    inline const PointVector& GetPoints(void) const { return points_; }

   private:
    // Attributes
    PointVector hull_;
    std::vector<Point> points_;

    //Methods
    double PointToPoint(const Point& point1, const Point& point2) const;
    void QuickHull(const Line &line, int side);
    double Distance(const Line &line, const Point &point) const;
    int FindSide(const Line &line, const Point &point) const;
    void XBounds(Point &min_x, Point &max_x) const;
    double PointToLine(const Line &line, const Point &point) const;
    bool FarthestPoint(const Line &line, int side, Point &farthest) const;
  };
}

#endif
