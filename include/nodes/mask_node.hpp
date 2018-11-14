#ifndef MASK_NODE_HPP_
#define MASK_NODE_HPP_

#include "node.hpp"
#include "point.hpp"

template <typename T>
class MaskNode : public Node<T>
{
    private:
        Node<T> *input;
        Node<bool> *mask;
        T default_value;

    public:
        MaskNode(Node<T> *input, Node<bool> *mask, T default_value);

        T get_voxel(const Point & pos) override;
};

template <typename T>
MaskNode<T>::MaskNode(Node<T> *input, Node<bool> *mask, T default_value)
    : input(input), mask(mask), default_value(default_value)
{}

template <typename T>
T MaskNode<T>::get_voxel(const Point & pos)
{
    return mask->get_voxel(pos) ? input->get_voxel(pos) : default_value;
}

#endif // MASK_NODE_HPP_
