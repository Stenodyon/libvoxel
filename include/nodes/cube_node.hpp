#ifndef CUBE_NODE_HPP_
#define CUBE_NODE_HPP_

#include "node.hpp"
#include "point.hpp"

template <typename T>
class CubeNode : public Node<T>
{
    private:
        int size;
        T inside, outside;

        bool is_inside(const Point & pos) const;

    public:
        CubeNode(int size, T inside, T outside);

        T get_voxel(const Point & pos) override;
};

template <typename T>
CubeNode<T>::CubeNode(int size, T inside, T outside)
    : size(size), inside(inside), outside(outside)
{
}

template <typename T>
bool CubeNode<T>::is_inside(const Point & pos) const
{
    return (pos.x <= size)
        && (pos.x >= -size)
        && (pos.y <= size)
        && (pos.y >= -size)
        && (pos.z <= size)
        && (pos.z >= -size);
}


template <typename T>
T CubeNode<T>::get_voxel(const Point & pos)
{
    return is_inside(pos) ? inside : outside;
}

#endif // CUBE_NODE_HPP_
