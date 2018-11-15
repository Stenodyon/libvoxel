#include <utility>

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