#include "nodes/or_node.hpp"

ORNode::ORNode(Node<bool> *rhs, Node<bool> *lhs)
    : rhs(rhs), lhs(lhs)
{
}

bool ORNode::get_voxel(const Point & pos)
{
    return (rhs->get_voxel(pos) || lhs->get_voxel(pos));
}
