#include "exporters.hpp"

#include <fstream>
#include <cstdint>
#include <unordered_set>

#include "vox_riff.hpp"

std::unordered_set<Point> render(Node<bool> *root, const BoxArea &area)
{
    std::unordered_set<Point> points;
    for (const auto& point : area)
    {
        if (root->get_voxel(point))
            points.insert(point);
    }
    return points;
}

void export_vox_shape(
        Node<bool> *root,
        const BoxArea &area,
        const std::string &filename)
{
    auto main = RiffMAIN();
    auto size = RiffSIZE(area.size_x(), area.size_y(), area.size_z());

    std::unordered_set<Point> points = render(root, area);
    auto xyzi = RiffXYZI();
    for (const auto& point : points)
        xyzi.add(point, 1);

    main.add_child(&size);
    main.add_child(&xyzi);

    auto stream = std::ofstream(filename, std::ios::binary);
    stream.write("VOX ", 4);
    write<uint32_t>(stream, 150);
    stream << (&main);
}
