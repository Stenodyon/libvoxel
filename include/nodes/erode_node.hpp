#ifndef ERODE_NODE_HPP_
#define ERODE_NODE_HPP_

#include "node.hpp"
#include "point.hpp"

class ErodeNode : public Node<bool>
{
    private:
        Node<bool> *input;
        int size;

    public:
        ErodeNode(Node<bool> *input, int size = 1);

        bool get_voxel(const Point &pos) override;
};

#endif // ERODE_NODE_HPP_
