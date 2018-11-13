#ifndef NOT_NODE_HPP_
#define NOT_NODE_HPP_

#include "node.hpp"

class NOTNode : public Node<bool>
{
    private:
        Node<bool> *input;

    public:
        explicit NOTNode(Node<bool> *input);

        bool get_voxel(const Point & pos) override;
};

#endif // NOT_NODE_HPP_
