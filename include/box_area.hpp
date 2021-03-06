#ifndef BOX_AREA_HPP_
#define BOX_AREA_HPP_

#include <iterator>
#include <vector>

#include "point.hpp"

class BoxArea
{
    private:
        Point lower, upper;

        class iterator : public std::iterator<
                         std::forward_iterator_tag,
                         Point, int, Point*, Point&>
        {
            private:
                const BoxArea &box;
                const Point &lower;

                int current;
                int layer_area, line_length;

                Point get() const;

            public:
                explicit iterator(const BoxArea &box, bool end = false);
                iterator& operator++();
                iterator operator++(int);
                bool operator==(iterator other) const;
                bool operator!=(iterator other) const;
                Point operator*() const;
        };

    public:
        BoxArea(const Point & corner1, const Point & corner2);
        iterator begin() const;
        iterator end() const;

        const Point & lower_corner() const;
        const Point & upper_corner() const;

        int size_x() const;
        int size_y() const;
        int size_z() const;
        int voxel_count() const;

        BoxArea face_xl() const;
        BoxArea face_xu() const;
        BoxArea face_yl() const;
        BoxArea face_yu() const;
        BoxArea face_zl() const;
        BoxArea face_zu() const;

        bool contains(const Point & point) const;

        BoxArea inside(int size = 1) const;
        BoxArea outside(int size = 1) const;

        std::vector<BoxArea> dice(int max_x, int max_y, int max_z) const;
};

#endif // BOX_AREA_HPP_
