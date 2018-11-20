#ifndef VOX_PALETTE_HPP_
#define VOX_PALETTE_HPP_

#include <array>
#include <cstdint>

class VoxPalette : public std::array<uint32_t, 256>
{
    private:
    public:
        void set_color(uint8_t color_id,
                uint8_t r, uint8_t g, uint8_t b, uint8_t a);
};

#endif // VOX_PALETTE_HPP_
