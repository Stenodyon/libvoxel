#include "nodes/solid_node.hpp"

template <typename VoxelType>
SolidNode<VoxelType>::SolidNode(VoxelType && value)
    : value(std::forward<VoxelType>(value))
{
}

template <typename VoxelType>
VoxelType SolidNode<VoxelType>::get_voxel(const Point & pos)
{
    return value;
}
