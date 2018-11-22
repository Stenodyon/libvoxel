#include "exporters.hpp"
#include "vox_riff.hpp"

void export_vox(
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

    std::vector<RiffChunk*> heap_chunks;

    if (palette != nullptr)
    {
        auto rgba = new RiffRGBA();
        heap_chunks.push_back(rgba);
        rgba->set_palette(*palette);
        main.add_child(rgba);

        for (const auto& material : palette->materials)
        {
            auto matt = new RiffMATT();
            heap_chunks.push_back(matt);
            matt->set_material(material);
            main.add_child(matt);
        }
    }

    for (auto& ptr : heap_chunks)
        delete ptr;

    auto stream = std::ofstream(filename, std::ios::binary);
    stream.write("VOX ", 4);
    write<uint32_t>(stream, 150);
    stream << (&main);
}
