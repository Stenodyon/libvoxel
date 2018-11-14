#ifndef AND_NODE_HPP_
#define AND_NODE_HPP_

#include "node.hpp"
#include "point.hpp"

class ANDNode : public Node<bool>
{
    private:
        Node<bool> *rhs, *lhs;

    public:
        ANDNode(Node<bool> *rhs, Node<bool> *lhs);

        bool get_voxel(const Point & pos) override;
};

#endif // AND_NODE_HPP_
