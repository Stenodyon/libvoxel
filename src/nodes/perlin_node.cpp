#include "nodes/perlin_node.hpp"

PerlinNode::PerlinNode(int seed, int octave)
    : perlin(seed), octave(octave)
{
}

double PerlinNode::get_voxel(const Point &pos)
{
    auto vec = Vec3f{pos} * octave / 128.;
    return perlin.noise0_1(vec.x, vec.y, vec.z);
}
