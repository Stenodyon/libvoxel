#ifndef SOLID_NODE_HPP_
#define SOLID_NODE_HPP_

#include "node.hpp"
#include "point.hpp"

template <typename VoxelType>
class SolidNode : public Node<VoxelType>
{
private:
    VoxelType value;

public:
    explicit SolidNode(VoxelType && value);

    VoxelType get_voxel(const Point & pos) override;
};

#endif // SOLID_NODE_HPP_
