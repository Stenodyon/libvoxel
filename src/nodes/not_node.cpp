#include "nodes/not_node.hpp"

NOTNode::NOTNode(Node<bool> *input) : input(input) {}

bool NOTNode::get_voxel(const Point &pos)
{
    return !(input->get_voxel(pos));
}
