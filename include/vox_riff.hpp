#ifndef VOX_RIFF_HPP_
#define VOX_RIFF_HPP_

#include <tuple>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include <unordered_set>

#include "point.hpp"
#include "vox_palette.hpp"

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
        virtual ~RiffChunk() = default;
        virtual std::string get_name() const = 0;

        void add_child(RiffChunk *child);
        const std::vector<RiffChunk*>& get_children() const;

        virtual uint32_t contents_size() const = 0;
        uint32_t children_size() const;
        uint32_t size() const;

        virtual void output_contents(std::ofstream &out) const = 0;
        friend std::ofstream& operator<<(std::ofstream &out, const RiffChunk *chunk);
};

///////////////////////////////////////////////////////////////////////////////
// SIZE ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class RiffSIZE : public RiffChunk
{
    private:
        uint32_t size_x, size_y, size_z;

    public:
        RiffSIZE(uint32_t size_x, uint32_t size_y, uint32_t size_z);
        std::string get_name() const override;
        uint32_t contents_size() const override;
        void output_contents(std::ofstream&) const override;
};

///////////////////////////////////////////////////////////////////////////////
// XYZI ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> xyzi_datum;

template <>
struct std::hash<xyzi_datum>
{
    std::size_t operator()(const xyzi_datum &datum) const
    {
        std::size_t seed = 4;
        seed ^= std::get<0>(datum) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::get<1>(datum) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::get<2>(datum) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::get<3>(datum) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

class RiffXYZI : public RiffChunk
{
    private:
        std::unordered_set<xyzi_datum> data;

    public:
        RiffXYZI();
        void add(uint8_t x, uint8_t y, uint8_t z, uint8_t color);
        void add(const Point &point, uint8_t color);
        std::string get_name() const override;
        uint32_t contents_size() const override;
        void output_contents(std::ofstream&) const override;
};

///////////////////////////////////////////////////////////////////////////////
// RGBA ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class RiffRGBA : public RiffChunk
{
    private:
        uint32_t palette[256];

    public:
        RiffRGBA();
        void set_color(uint8_t color_id,
                uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        void set_palette(const VoxPalette &palette);
        std::string get_name() const override;
        uint32_t contents_size() const override;
        void output_contents(std::ofstream&) const override;
};

///////////////////////////////////////////////////////////////////////////////
// MATT ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class RiffMATT : public RiffChunk
{
    private:
        VoxMaterial material;

    public:
        RiffMATT();
        void set_material(VoxMaterial material);
        std::string get_name() const override;
        uint32_t contents_size() const override;
        void output_contents(std::ofstream&) const override;
};

///////////////////////////////////////////////////////////////////////////////
// MAIN ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class RiffMAIN : public RiffChunk
{
    public:
        RiffMAIN();
        std::string get_name() const override;
        uint32_t contents_size() const override;
        void output_contents(std::ofstream&) const override;
};

#endif // VOX_RIFF_HPP_
