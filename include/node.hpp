#ifndef NODE_HPP_
#define NODE_HPP_

#include "graph_node.hpp"
#include "point.hpp"

template <typename VoxelType>
class Node : public GraphNode
{
    public:
        virtual VoxelType get_voxel(const Point & pos) = 0;
};

#endif // NODE_HPP_
