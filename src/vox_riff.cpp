#include "vox_riff.hpp"

void RiffChunk::add_child(RiffChunk *child)
{
    children.push_back(child);
}

const std::vector<RiffChunk*>& RiffChunk::get_children() const
{
    return children;
}

uint32_t RiffChunk::children_size() const
{
    uint32_t size = 0;
    for (auto &child : children)
        size += child->size();
    return size;
}

uint32_t RiffChunk::size() const
{
    uint32_t header = 12;
    uint32_t contents = contents_size();
    uint32_t children = children_size();

    return header + contents + children;
}

std::ofstream& operator<<(std::ofstream &out, const RiffChunk *chunk)
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

///////////////////////////////////////////////////////////////////////////////
// SIZE ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RiffSIZE::RiffSIZE(uint32_t size_x, uint32_t size_y, uint32_t size_z)
    : size_x(size_x), size_y(size_y), size_z(size_z)
{
}

std::string RiffSIZE::get_name() const { return "SIZE"; }

uint32_t RiffSIZE::contents_size() const { return 12; }

void RiffSIZE::output_contents(std::ofstream &out) const
{
    write<uint32_t>(out, size_x);
    write<uint32_t>(out, size_y);
    write<uint32_t>(out, size_z);
}

///////////////////////////////////////////////////////////////////////////////
// XYZI ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RiffXYZI::RiffXYZI() {}

void RiffXYZI::add(uint8_t x, uint8_t y, uint8_t z, uint8_t color)
{
    data.insert({x, y, z, color});
}

void RiffXYZI::add(const Point &point, uint8_t color)
{
    data.insert({
            (uint8_t)point.x,
            (uint8_t)point.y,
            (uint8_t)point.z,
            color
            });
}

std::string RiffXYZI::get_name() const { return "XYZI"; }

uint32_t RiffXYZI::contents_size() const
{
    return 4 + 4 * data.size();
}

void RiffXYZI::output_contents(std::ofstream &out) const
{
    write<uint32_t>(out, data.size());
    for (const auto& datum : data)
    {
        write<uint8_t>(out, std::get<0>(datum));
        write<uint8_t>(out, std::get<1>(datum));
        write<uint8_t>(out, std::get<2>(datum));
        write<uint8_t>(out, std::get<3>(datum));
    }
}

///////////////////////////////////////////////////////////////////////////////
// RGBA ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RiffRGBA::RiffRGBA()
{
    palette[0] = 0x00000000; // ??
}

void RiffRGBA::set_color(uint8_t color_id,
        uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    palette[color_id] =
        ((uint32_t)a << 24) +
        ((uint32_t)b << 16) +
        ((uint32_t)g << 8) +
        r;
}

void RiffRGBA::set_palette(const VoxPalette &new_palette)
{
    for (int i = 0; i < new_palette.colors.size(); i++)
        this->palette[i] = new_palette.colors[i];
}

std::string RiffRGBA::get_name() const
{
    return "RGBA";
}

uint32_t RiffRGBA::contents_size() const
{
    return 4 * 256;
}

void RiffRGBA::output_contents(std::ofstream& out) const
{
    for (const auto& color : palette)
        write<uint32_t>(out, color);
}

///////////////////////////////////////////////////////////////////////////////
// MATT ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RiffMATT::RiffMATT()
{
}

void RiffMATT::set_material(VoxMaterial material)
{
    this->material = material;
}

std::string RiffMATT::get_name() const
{
    return "MATT";
}

uint32_t RiffMATT::contents_size() const
{
    int bits_sets = 0;
    for (auto& bit : material.property_bits)
        if (bit == true) bits_sets++;

    return 16 + 4 * bits_sets;
}

void RiffMATT::output_contents(std::ofstream& out) const
{
    write<uint32_t>(out, material.id);
    write<uint32_t>(out, material.type);
    write<float>(out, material.weight);

    uint32_t bit_field = 0;
    for (int i = 0; i < 8; i++)
        if (material.property_bits[i]) bit_field += 1 << i;
    write<uint32_t>(out, bit_field);

    for (int i = 0; i < 7; i++)
        if (material.property_bits[i])
            write<float>(out, material.property_values[i]);
}


///////////////////////////////////////////////////////////////////////////////
// MAIN ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RiffMAIN::RiffMAIN() {}

std::string RiffMAIN::get_name() const { return "MAIN"; }

uint32_t RiffMAIN::contents_size() const { return 0; }

void RiffMAIN::output_contents(std::ofstream&) const {}
