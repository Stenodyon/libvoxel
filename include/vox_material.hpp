#ifndef VOX_MATERIAL_HPP_
#define VOX_MATERIAL_HPP_

#include <cstdint>

struct VoxMaterial
{
    enum Type
    {
        DIFFUSE  = 0,
        GLASS    = 1,
        METAL    = 2,
        EMISSIVE = 3
    };

    enum Property
    {
        PLASTIC        = 0,
        ROUGHNESS      = 1,
        SPECULAR       = 2,
        IOR            = 3,
        ATTENUATION    = 4,
        POWER          = 5,
        GLOW           = 6,
        IS_TOTAL_POWER = 7
    };

    uint32_t id;
    Type type;
    float weight;
    bool property_bits[8];
    float property_values[7];

    VoxMaterial(Type type = DIFFUSE);
    void set_property(Property property, bool value);

};

#endif // VOX_MATERIAL_HPP_
