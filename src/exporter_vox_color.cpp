#include "exporters.hpp"

#include "vox_riff.hpp"

void export_vox_color(
        Node<uint8_t> *root,
        const VoxPalette *palette,
        const BoxArea &area,
        const std::string &filename)
{
    auto main = RiffMAIN();
    auto size = RiffSIZE(area.size_x(), area.size_y(), area.size_z());

    auto xyzi = RiffXYZI();
    for (const auto& point : area)
    {
        if (uint8_t color = root->get_voxel(point); color > 0)
            xyzi.add(point, color);
    }

    main.add_child(&size);
    main.add_child(&xyzi);

    if (palette != nullptr)
    {
        auto rgba = RiffRGBA();
        rgba.set_palette(*palette);
        main.add_child(&rgba);
    }

    auto stream = std::ofstream(filename, std::ios::binary);
    stream.write("VOX ", 4);
    write<uint32_t>(stream, 150);
    stream << (&main);
}
