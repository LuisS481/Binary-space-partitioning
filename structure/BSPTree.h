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

    // Método de inserción recursivo
    BSPTreeNode* insertarBSPTree(BSPTreeNode* node, const Polygon& p){
        if (!node) {
            // Si llegamos a un nodo vacío, creamos un nuevo nodo con el polígono como plano de particion
            BSPTreeNode* newNode = new BSPTreeNode(p.normal().x, p.normal().y, p.normal().z,
                                                   -(p.normal().x * p.vertex[0].x + p.normal().y * p.vertex[0].y + p.normal().z * p.vertex[0].z));
            newNode->polygons.push_back(p);
            return newNode;
        }

        // Calcular la posición del polígono con respecto al plano del nodo actual
        float A = node->A, B = node->B, C = node->C, D = node->D;
        if (p.isFrontOf(A, B, C, D)) {
            // Si está completamente frente al plano, insertamos en el nodo frontal
            node->front = insertarBSPTree(node->front, p);
        } else if (p.isBackOf(A, B, C, D)) {
            // Si está completamente detrás del plano, insertamos en el nodo trasero
            node->back = insertarBSPTree(node->back, p);
        } else {
            // Si el polígono cruza el plano, lo dividimos y lo insertamos recursivamente
            Polygon frontPart, backPart;
            p.divide(A, B, C, D, frontPart, backPart);

            node->front = insertarBSPTree(node->front, frontPart);
            node->back = insertarBSPTree(node->back, backPart);
        }

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

    // Método público para insertar un polígono en el BSP
    void insertarPoligono(const Polygon& p){
        root = insertarBSPTree(root, p);
    }
};
