#include "nodes/and_node.hpp"

ANDNode::ANDNode(Node<bool> *rhs, Node<bool> *lhs)
    : rhs(rhs), lhs(lhs)
{
}

bool ANDNode::get_voxel(const Point & pos)
{
    return (rhs->get_voxel(pos) && lhs->get_voxel(pos));
}
