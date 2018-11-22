#ifndef VOX_PALETTE_HPP_
#define VOX_PALETTE_HPP_

#include <array>
#include <vector>
#include <cstdint>

#include "vox_material.hpp"

struct VoxPalette
{
    std::array<uint32_t, 256> colors;
    std::vector<VoxMaterial> materials;

    void set_color(uint8_t color_id, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void add_material(VoxMaterial material);
};

#endif // VOX_PALETTE_HPP_
