#ifndef PERLIN_NODE_HPP
#define PERLIN_NODE_HPP

#include "PerlinNoise.hpp"

#include "node.hpp"
#include "point.hpp"

class PerlinNode : public Node<double>
{
    private:
        siv::PerlinNoise perlin;
        int octave;

    public:
        PerlinNode(int seed, int octave);

        double get_voxel(const Point &pos) override;
};

#endif // PERLIN_NODE_HPP
