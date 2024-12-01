#include "node.h"
#include "R3.h"


class BSPTree{
private:
  BSPTreeNode *root;

  BSPTreeNode* buildBSPTree(std::vector<Polygon>& polygons){
    if (polygons.empty()) return nullptr;

    Polygon& partition = polygons[0];
    
    // float A = 0, B = 0, C = 0, D = 0;
    // Calcula los coeficientes del plano
    R3 n = partition.normal();
    float A = n.x, B = n.y, C = n.z;
    float D = -(A*partition.vertex[0].x + B*partition.vertex[0].y + C*partition.vertex[0].z);
    
    std::vector<Polygon> frontPolygons;
    std::vector<Polygon> backPolygons;

    for (int i = 0; i < polygons.size(); i++){
      const Polygon& polygon = polygons[i];
      if (polygon.isFrontOf(A, B, C, D)){
        frontPolygons.push_back(polygon);
      } else if (polygon.isBackOf(A, B, C, D)){
        backPolygons.push_back(polygon);
      } else {
        Polygon front, back;
        polygon.divide(A, B, C, D, front, back);
        frontPolygons.push_back(front);
        backPolygons.push_back(back);
      }
    }

    // Crea nodo actual
    BSPTreeNode* node = new BSPTreeNode(A, B, C, D);
    node->polygons.push_back(partition);
    
    // Recursividad
    node->front = buildBSPTree(frontPolygons);
    node->back = buildBSPTree(backPolygons);
    
    return node;
  }

  // Eliminar árbol
  void deleteTree(BSPTreeNode* node) {
        if (!node) return;
        deleteTree(node->front);
        deleteTree(node->back);
        delete node;
    }

public:

    // Constructor
    BSPTree(std::vector<Polygon>& polygons) {
        root = buildBSPTree(polygons);
    }

    // Destructor
    ~BSPTree() {
        deleteTree(root);
    }   

};
