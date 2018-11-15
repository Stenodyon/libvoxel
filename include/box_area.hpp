#ifndef BOX_AREA_HPP_
#define BOX_AREA_HPP_

#include "point.hpp"

class BoxArea
{
    private:
        Point lower, upper;

    public:
        BoxArea(const Point & corner1, const Point & corner2);
        //begin()
        //end()

        const Point & lower_corner() const;
        const Point & upper_corner() const;

        int size_x() const;
        int size_y() const;
        int size_z() const;

        BoxArea face_xl() const;
        BoxArea face_xu() const;
        BoxArea face_yl() const;
        BoxArea face_yu() const;
        BoxArea face_zl() const;
        BoxArea face_zu() const;

        BoxArea inside(int size) const;
        BoxArea outside(int size) const;
};

#endif // BOX_AREA_HPP_
