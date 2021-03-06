#include <fstream>
#include <vector>
#include <unordered_map>
#include <array>

#include "exporters.hpp"

class IndexTable
{
    private:
        std::unordered_map<Point, int> indices;
        std::vector<const Point*> points;

        class iterator : public std::iterator<
                                std::forward_iterator_tag,
                                Point, int, Point*, Point&>
        {
            private:
                std::vector<const Point*> &points;
                int current, last;

            public:
                explicit iterator(std::vector<const Point*> &points, bool end=false)
                    : points(points), current(0), last(points.size())
                {
                    if (end) current = last;
                }

                iterator& operator++()
                {
                    current++;
                    return *this;
                }
                iterator operator++(int)
                {
                    auto prev_value = *this;
                    current++;
                    return prev_value;
                }

                bool operator==(iterator other) const
                {
                    return (&points == &other.points)
                        && (current == other.current);
                }
                bool operator!=(iterator other) const
                {
                    return !(*this == other);
                }

                Point operator*() const
                {
                    return *(points[current]);
                }
        };

    public:
        size_t size() const
        {
            return indices.size();
        }

        int operator[](const Point& point)
        {
            if (auto iter = indices.find(point); iter != indices.end())
                return iter->second;

            int id = points.size();
            indices.insert({point, id});
            points.push_back(&(indices.find(point)->first));
            return id;
        }
        Point operator[](int index)
        {
            return *(points[index]);
        }

        iterator begin()
        {
            return iterator{points};
        }
        iterator end()
        {
            return iterator{points, true};
        }
};

using VertexNormal = std::pair<int, int>;
using Face = std::array<VertexNormal, 3>;

const Point up       = { 0,  0,  1};
const Point down     = { 0,  0, -1};
const Point forward  = { 0,  1,  0};
const Point backward = { 0, -1,  0};
const Point right    = { 1,  0,  0};
const Point left     = {-1,  0,  0};

#define MAKE_FACE(a, b, c, d, normal)                    \
    if (!root->get_voxel(point + normal))                \
    {                                                    \
        faces.push_back({{                               \
                {vertex_index[a], normal_index[normal]}, \
                {vertex_index[b], normal_index[normal]}, \
                {vertex_index[c], normal_index[normal]}, \
                }});                                     \
        faces.push_back({{                               \
                {vertex_index[b], normal_index[normal]}, \
                {vertex_index[c], normal_index[normal]}, \
                {vertex_index[d], normal_index[normal]}  \
                }});                                     \
    }

void export_obj_shape(Node<bool> *root,
                      BoxArea area,
                      const std::string &filename)
{
    IndexTable vertex_index;
    IndexTable normal_index;
    std::vector<Face> faces;

    for (const auto& point : area)
    {
        if (!root->get_voxel(point))
            continue;

        const Point a = point + Point{0, 0, 0};
        const Point b = point + Point{1, 0, 0};
        const Point c = point + Point{0, 1, 0};
        const Point d = point + Point{1, 1, 0};

        const Point f = point + Point{0, 0, 1};
        const Point g = point + Point{1, 0, 1};
        const Point h = point + Point{0, 1, 1};
        const Point i = point + Point{1, 1, 1};

        MAKE_FACE(a, b, c, d, down);
        MAKE_FACE(f, g, h, i, up);
        MAKE_FACE(c, d, h, i, forward);
        MAKE_FACE(a, b, f, g, backward);
        MAKE_FACE(a, c, f, h, left);
        MAKE_FACE(b, d, g, i, right);
    }

    std::cout << vertex_index.size() << " vertices, "
        << normal_index.size() << " normals, "
        << faces.size() << " faces" << std::endl;

    std::ofstream out{filename};

    out << "# Wavefront OBJ" << std::endl
        << "# Auto-generated by libvoxel" << std::endl << std::endl;

    for (const auto& point : vertex_index)
    {
        auto vertex = (Vertex)point;
        out << "v "
            << vertex.x << " "
            << vertex.y << " "
            << vertex.z << std::endl;
    }

    out << std::endl;

    for (const auto& point : normal_index)
    {
        auto normal = (Vertex)point;
        out << "vn "
            << normal.x << " "
            << normal.y << " "
            << normal.z << std::endl;
    }

    out << std::endl;

    for (const auto& face : faces)
    {
        out << "f ";
        for (const auto& [vertex_id, normal_id] : face)
            out << vertex_id + 1 << "//" << normal_id + 1 << " ";
        out << std::endl;
    }
}
