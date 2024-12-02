#ifndef POLYGON_H
#define POLYGON_H

#include "R3.h"
#include <vector>

struct Polygon{
  // Vértices del Polígono, R3 puntos en el espacio 3D
  std::vector<R3> vertex;

  Polygon(){}
  Polygon(const std::vector<R3>& vertex): vertex(vertex){}

  bool isFrontOf(float A, float B, float C, float D) const {
    for (const auto& v : vertex){
      if (A*v.x + B*v.y + C*v.z + D < 0){
        return false;
      }
    }
    return true;
  }

  bool isBackOf(float A, float B, float C, float D) const {
    for (const auto& v : vertex){
      if (A*v.x + B*v.y + C*v.z + D > 0){
        return false;
      }
    }
    return true;
  }

  bool crossesPlane(float A, float B, float C, float D) const {
    bool front = false;
    bool back = false;

    for (const auto& v:vertex){
      float distance = A*v.x + B*v.y + C*v.z + D;
      if (distance > 0) front = true; 
      if (distance < 0) back = true;
      if (front && back) return true;
    }
    return false;
  }

  void divide(float A, float B, float C, float D, Polygon &front, Polygon &back) const {
    std::vector<R3> frontVertex;
    std::vector<R3> backVertex;

    for (int i = 0; i < vertex.size(); i++){
      const R3& v1 = vertex[i];
      const R3& v2 = vertex[(i+1)%vertex.size()];
      float d1 = A*v1.x + B*v1.y + C*v1.z + D;
      float d2 = A*v2.x + B*v2.y + C*v2.z + D;

      if (d1 >= 0) frontVertex.push_back(v1);
      if (d1 <= 0) backVertex.push_back(v1);

      if ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)){
        float t = d1/(d1 - d2);
        R3 intersection = {v1.x + t*(v2.x - v1.x), v1.y + t*(v2.y - v1.y), v1.z + t*(v2.z - v1.z)};
        frontVertex.push_back(intersection);
        backVertex.push_back(intersection);
      }
    }
    front = Polygon(frontVertex);
    back = Polygon(backVertex);
  }

  R3 normal() const {
    if (vertex.size() < 3) return R3();
    R3 v1 = vertex[1] - vertex[0];
    R3 v2 = vertex[2] - vertex[0];
    return (v1*v2).normilize();
  }

  bool isInside(const R3& point) const {
    R3 n = normal();
    for (int i = 0; i < vertex.size(); i++){
      const R3& v1 = vertex[i];
      const R3& v2 = vertex[(i+1)%vertex.size()];
      R3 edge = v2 - v1;
      R3 toPoint = point - v1;
      if (n.dot(edge*toPoint) < 0) return false;
    }
    return true;
  }

  bool intersects(const Polygon &other) const{
    for (const auto &v : vertex){
      if (other.isInside(v)) return true;
    }
    for (const auto &v : other.vertex){
      if (isInside(v)) return true;
    }
    return false;
  }
};

#endif // !POLYGON_H
