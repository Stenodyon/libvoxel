#include "nodes/erode_node.hpp"
#include "box_area.hpp"

ErodeNode::ErodeNode(Node<bool> *input, int size)
    : input(input), size(size)
{
}

bool ErodeNode::get_voxel(const Point &pos)
{
    for (const auto& dp : BoxArea{{-size, -size, -size}, {size, size, size}})
    {
        if (!input->get_voxel(pos + dp))
            return false;
    }
    return true;
}
