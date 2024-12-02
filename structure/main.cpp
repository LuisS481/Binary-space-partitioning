#include "BSPTree.h" 
#include <iostream>
int main() {
    Polygon polygon1({
        R3(0, 0, 0),
        R3(1, 0, 0),
        R3(0, 1, 0)
    });
    Polygon polygon2({
        R3(1, 0, 0),
        R3(1, 1, 0),
        R3(0, 1, 0)
    });
    Polygon polygon3({
        R3(0, 0, 1),
        R3(1, 0, 1),
        R3(0, 1, 1)
    });
    std::vector<Polygon> polygons = {polygon1, polygon2, polygon3};
    for (const auto& polygon : polygons) {
    if (polygon.vertex.size() < 3) {
        std::cout << "Inválido, tiene menos de 3 vértices" << std::endl;
        return -1;
    }
}
    BSPTree bsptree(polygons);

    // Ahora, insertamos un nuevo polígono
    Polygon newPolygon({
                               R3(0, 0, 1),
                               R3(1, 0, 1),
                               R3(0, 1, 1)
                       });
    bsptree.insertarPoligono(newPolygon);  // Insertamos el nuevo polígono

    // tree.print(); // Falta
    return 0;
}
