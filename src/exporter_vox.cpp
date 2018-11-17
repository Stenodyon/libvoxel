#include "exporters.hpp"

#include <vector>
#include <fstream>
#include <cstdint>
#include <unordered_set>

template <typename T, typename Arg>
static inline
void write(std::ofstream &out, Arg value)
{
    T buffer = (T)value;
    out.write((char*)&buffer, sizeof(T));
}

class RiffChunk
{
    private:
        std::vector<RiffChunk*> children;

    public:
        virtual std::string get_name() const = 0;

        void add_child(RiffChunk *child)
        {
            children.push_back(child);
        }
        const std::vector<RiffChunk*> & get_children() const
        {
            return children;
        }

        virtual uint32_t contents_size() const = 0;
        uint32_t children_size() const
        {
            uint32_t size = 0;
            for (auto &child : children)
                size += child->size();
            return size;
        }
        uint32_t size() const
        {
            uint32_t header = 12;
            uint32_t contents = contents_size();
            uint32_t children = children_size();

            return header + contents + children;
        }

        virtual void output_contents(std::ofstream &out) const = 0;
        friend std::ofstream& operator<<(std::ofstream &out, const RiffChunk *chunk)
        {
            std::string name = chunk->get_name();
            out.write(name.c_str(), 4);
            write<uint32_t>(out, chunk->contents_size());
            write<uint32_t>(out, chunk->children_size());

            chunk->output_contents(out);
            for (const auto& child : chunk->children)
                out << child;

            return out;
        }
};

class RiffSIZE : public RiffChunk
{
    private:
        uint32_t size_x, size_y, size_z;

    public:
        RiffSIZE(uint32_t size_x, uint32_t size_y, uint32_t size_z)
            : size_x(size_x), size_y(size_y), size_z(size_z)
        {
        }

        std::string get_name() const override { return "SIZE"; }

        uint32_t contents_size() const override { return 12; }

        void output_contents(std::ofstream &out) const override
        {
            write<uint32_t>(out, size_x);
            write<uint32_t>(out, size_y);
            write<uint32_t>(out, size_z);
        }
};

class RiffXYZI : public RiffChunk
{
    private:
        const std::unordered_set<Point> &points;

    public:
        RiffXYZI(const std::unordered_set<Point> &points)
            : points(points)
        {
        }

        std::string get_name() const override { return "XYZI"; }

        uint32_t contents_size() const override
        {
            return 4 + 4 * points.size();
        }

        void output_contents(std::ofstream &out) const override
        {
            write<uint32_t>(out, points.size());
            for (const auto& point : points)
            {
                write<uint8_t>(out, point.x);
                write<uint8_t>(out, point.y);
                write<uint8_t>(out, point.z);
                write<uint8_t>(out, 0x4F);
            }
        }
};

class RiffMAIN : public RiffChunk
{
    private:
    public:
        RiffMAIN() {}

        std::string get_name() const override { return "MAIN"; }

        uint32_t contents_size() const override { return 0; }

        void output_contents(std::ofstream&) const override {}
};

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
        BoxArea area,
        const std::string &filename)
{
    auto main = RiffMAIN();
    auto size = RiffSIZE(area.size_x(), area.size_y(), area.size_z());

    std::unordered_set<Point> points = render(root, area);
    auto xyzi = RiffXYZI(points);

    main.add_child(&size);
    main.add_child(&xyzi);

    auto stream = std::ofstream(filename, std::ios::binary);
    stream.write("VOX ", 4);
    write<uint32_t>(stream, 150);
    stream << (&main);
}
