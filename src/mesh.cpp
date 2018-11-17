#include "mesh.hpp"

Mesh::Mesh() {}

Mesh::Mesh(std::vector<Vertex> vertices,
        std::vector<Vertex> normals,
        std::vector<int> indices)
    : vertices(vertices), normals(normals), indices(indices)
{
#ifdef _DEBUG
    // Mesh validation
    if (vertices.size() != normals.size())
    {
        std::cerr << "Warning, mesh has a different number of vertices than "
            "normals" << std::endl;
    }
    for (int index : indices)
    {
        if (index > vertices.size() || index > normals.size())
            std::cerr << "Warning, mesh index out of bounds: " << index
                << std::endl;
    }
#endif
}

Mesh Mesh::FromNode(Node<bool> *root, BoxArea area)
{
    // TODO Add some limits maybe?
    // TODO Implementation

    std::cerr << "Warning, Mesh::FromNode not implemented, returning empty"
        " mesh" << std::endl;
    return Mesh();
}
