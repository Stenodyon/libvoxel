#include "nodes/dilate_node.hpp"

DilateNode::DilateNode(Node<bool> *input, int size)
    : input(input), size(size)
{
}

bool DilateNode::get_voxel(const Point &pos)
{
    for (const auto& dp : BoxArea{{-size, -size, -size}, {size, size, size}})
    {
        if (input->get_voxel(pos + dp))
            return true;
    }
    return false;
}
