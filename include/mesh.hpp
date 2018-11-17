#ifndef MESH_HPP_
#define MESH_HPP_

#include <vector>

#include "node.hpp"
#include "point.hpp"
#include "box_area.hpp"

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<Vertex> normals;
    std::vector<int> indices;

    Mesh();
    Mesh(std::vector<Vertex> vertices,
            std::vector<Vertex> normals,
            std::vector<int> indices);
    
    static Mesh FromNode(Node<bool> *root, BoxArea area);
};

#endif // MESH_HPP_
