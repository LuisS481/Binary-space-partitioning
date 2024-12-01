#ifndef NODE_H
#define NODE_H

#include "polygon.h"

struct BSPTreeNode {
  // Ecuación Ax+By+Cz+D=0
  float A, B, C, D;

  std::vector<Polygon> polygons;
  BSPTreeNode *front; 
  BSPTreeNode *back;

  BSPTreeNode(float a, float b, float c, float d): A(a), B(b), C(c), D(d), front(nullptr), back(nullptr){}

  // Destructor para punteros, buena práctica jsjs
  ~BSPTreeNode() {
    delete front;
    delete back;
}
};

#endif // !NODE_H
