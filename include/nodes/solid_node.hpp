#ifndef SOLID_NODE_HPP_
#define SOLID_NODE_HPP_

#include <type_traits>

#include "node.hpp"
#include "point.hpp"

template <typename VoxelType>
class SolidNode : public Node<VoxelType>
{
private:
    VoxelType value;

public:
    explicit SolidNode(VoxelType value);

    VoxelType get_voxel(const Point & pos) override;
};

template <typename VoxelType>
SolidNode<VoxelType>::SolidNode(VoxelType value) : value(value) {}

template <typename VoxelType>
VoxelType SolidNode<VoxelType>::get_voxel(const Point &)
{
    return value;
}

#endif // SOLID_NODE_HPP_
