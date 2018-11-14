#ifndef OR_NODE_HPP_
#define OR_NODE_HPP_

#include "node.hpp"
#include "point.hpp"

class ORNode : public Node<bool>
{
    private:
        Node<bool> *rhs, *lhs;

    public:
        ORNode(Node<bool> *rhs, Node<bool> *lhs);

        bool get_voxel(const Point & pos) override;
};

#endif // OR_NODE_HPP_
