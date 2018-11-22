#include "vox_palette.hpp"

void VoxPalette::set_color(uint8_t color_id,
        uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    colors[color_id] = (a << 24) + (b << 16) + (g << 8) + r;
}

void VoxPalette::add_material(VoxMaterial material)
{
    materials.push_back(material);
}
