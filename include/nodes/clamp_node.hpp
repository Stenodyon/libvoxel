#ifndef CLAMP_NODE_HPP_
#define CLAMP_NODE_HPP_

#include "node.hpp"

template <typename T>
class ClampNode : public Node<T>
{
    private:
        Node<T> *input;
        T min, max;

    public:
        ClampNode(Node<T> *input, T min, T max);

        T get_voxel(const Point &pos) override;
};

template <typename T>
ClampNode<T>::ClampNode(Node<T> *input, T min, T max)
    : input(input), min(min), max(max)
{
}

template <typename T>
T ClampNode<T>::get_voxel(const Point &pos)
{
    return std::min(this->max, std::max(this->min, input->get_voxel(pos)));
}

#endif // CLAMP_NODE_HPP_
