#ifndef DILATE_NODE_HPP_
#define DILATE_NODE_HPP_

#include "node.hpp"
#include "point.hpp"
#include "box_area.hpp"

class DilateNode : public Node<bool>
{
    private:
        Node<bool> *input;
        int size;

    public:
        DilateNode(Node<bool> *input, int size);

        bool get_voxel(const Point &pos) override;
};

#endif // DILATE_NODE_HPP_
