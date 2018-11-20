#include <utility>
#include <algorithm>

#include "box_area.hpp"

BoxArea::BoxArea(const Point & corner1, const Point & corner2)
{
    const auto& [lower_x, upper_x] = corner1[0] < corner2[0] ?
          std::pair{corner1[0], corner2[0]}
        : std::pair{corner2[0], corner1[0]};
    const auto& [lower_y, upper_y] = corner1[1] < corner2[1] ?
          std::pair{corner1[1], corner2[1]}
        : std::pair{corner2[1], corner1[1]};
    const auto& [lower_z, upper_z] = corner1[2] < corner2[2] ?
          std::pair{corner1[2], corner2[2]}
        : std::pair{corner2[2], corner1[2]};

    lower = Point{lower_x, lower_y, lower_z};
    upper = Point{upper_x, upper_y, upper_z};
}

BoxArea::iterator BoxArea::begin() const
{
    return iterator(*this);
}

BoxArea::iterator BoxArea::end() const
{
    return iterator(*this, true);
}

const Point & BoxArea::lower_corner() const
{
    return lower;
}

const Point & BoxArea::upper_corner() const
{
    return upper;
}

int BoxArea::size_x() const
{
    return upper[0] - lower[0] + 1;
}

int BoxArea::size_y() const
{
    return upper[1] - lower[1] + 1;
}

int BoxArea::size_z() const
{
    return upper[2] - lower[2] + 1;
}

int BoxArea::voxel_count() const
{
    return size_x() * size_y() * size_z();
}

BoxArea BoxArea::face_xl() const
{
    Point face_upper = upper;
    face_upper[0] = lower[0];
    return BoxArea{lower, face_upper};
}

BoxArea BoxArea::face_xu() const
{
    Point face_lower = lower;
    face_lower[0] = upper[0];
    return BoxArea{face_lower, upper};
}

BoxArea BoxArea::face_yl() const
{
    Point face_upper = upper;
    face_upper[1] = lower[1];
    return BoxArea{lower, face_upper};
}

BoxArea BoxArea::face_yu() const
{
    Point face_lower = lower;
    face_lower[1] = upper[1];
    return BoxArea{face_lower, upper};
}

BoxArea BoxArea::face_zl() const
{
    Point face_upper = upper;
    face_upper[2] = lower[2];
    return BoxArea{lower, face_upper};
}

BoxArea BoxArea::face_zu() const
{
    Point face_lower = lower;
    face_lower[2] = upper[2];
    return BoxArea{face_lower, upper};
}

// ============================================================================

Point BoxArea::iterator::get() const
{
    const int z = current / layer_area;
    const int layer = current % layer_area;
    const int y = layer / line_length;
    const int x = layer % line_length;

    return lower + Point{x, y, z};
}

BoxArea::iterator::iterator(const BoxArea &box, bool end)
    : box(box), lower(box.lower_corner())
{
    current = end ? box.size_x() * box.size_y() * box.size_z() : 0;
    layer_area = box.size_x() * box.size_y();
    line_length = box.size_x();
}

BoxArea::iterator& BoxArea::iterator::operator++()
{
    current++;
    return *this;
}

BoxArea::iterator BoxArea::iterator::operator++(int)
{
    iterator retval = *this;
    ++(*this);
    return retval;
}

bool BoxArea::iterator::operator==(iterator other) const
{
    return (&box == &(other.box)) && (current == other.current);
}

bool BoxArea::iterator::operator!=(iterator other) const
{
    return !(*this == other);
}

Point BoxArea::iterator::operator*() const
{
    return get();
}

bool BoxArea::contains(const Point & point) const
{
    return (point.x >= lower.x)
        && (point.x <= upper.x)
        && (point.y >= lower.y)
        && (point.y <= upper.y)
        && (point.z >= lower.z)
        && (point.z <= upper.z);
}

BoxArea BoxArea::inside(int size) const
{
    return BoxArea{
        lower + Point{size, size, size},
        upper - Point{size, size, size},
    };
}

BoxArea BoxArea::outside(int size) const
{
    return BoxArea{
        lower - Point{size, size, size},
        upper + Point{size, size, size},
    };
}

std::vector<BoxArea> BoxArea::dice(int max_x, int max_y, int max_z) const
{
    int sizex = size_x();
    int sizey = size_y();
    int sizez = size_z();
    int count_x = (sizex + max_x - 1) / max_x;
    int count_y = (sizey + max_y - 1) / max_y;
    int count_z = (sizez + max_z - 1) / max_z;

    std::vector<BoxArea> diced;
    diced.reserve(count_x * count_y * count_z);
    for (int dice_x = 0; dice_x < count_x; dice_x++)
    {
        int subsize_x = std::min(sizex - dice_x * max_x, max_x);
        for (int dice_y = 0; dice_y < count_y; dice_y++)
        {
            int subsize_y = std::min(sizey - dice_y * max_y, max_y);
            for (int dice_z = 0; dice_z < count_z; dice_z++)
            {
                int subsize_z = std::min(sizez - dice_z * max_z, max_z);
                auto base = Point{
                    dice_x * max_x,
                    dice_y * max_y,
                    dice_z * max_z,
                };
                diced.push_back({
                        base,
                        base + Point{subsize_x, subsize_y, subsize_z}
                });
            }
        }
    }
    return diced;
}
