#ifndef SQUISH_NODE_HPP_
#define SQUISH_NODE_HPP_

#include "node.hpp"
#include "point.hpp"

template <typename T>
class SquishNode : public Node<T>
{
    private:
        Node<T> *input;
        Vec3f direction;

    public:
        SquishNode(Node<T> *input, double vertical_squish);
        SquishNode(Node<T> *input, Vec3f squish_factor);

        T get_voxel(const Point &pos) override;
};

template <typename T>
SquishNode<T>::SquishNode(Node<T> *input, double vertical_squish)
    : input(input), direction({1., 1., vertical_squish})
{
}

template <typename T>
SquishNode<T>::SquishNode(Node<T> *input, Vec3f squish_factor)
    : input(input), direction(squish_factor)
{
}

template <typename T>
T SquishNode<T>::get_voxel(const Point &pos)
{
    return input->get_voxel(Point{pos & direction});
}

#endif // SQUISH_NODE_HPP_
