#ifndef MULTIPLY_NODE_HPP_
#define MULTIPLY_NODE_HPP_

#include "node.hpp"

template <typename T>
class MultiplyNode : public Node<T>
{
    private:
        Node<T> *rhs, *lhs;

    public:
        MultiplyNode(Node<T> *rhs, Node<T> *lhs);

        T get_voxel(const Point & pos) override;
};

template <typename T>
MultiplyNode<T>::MultiplyNode(Node<T> *rhs, Node<T> *lhs)
    : rhs(rhs), lhs(lhs)
{
}

template <typename T>
T MultiplyNode<T>::get_voxel(const Point & pos)
{
    return rhs->get_voxel(pos) * lhs->get_voxel(pos);
}

#endif // MULTIPLY_NODE_HPP_
