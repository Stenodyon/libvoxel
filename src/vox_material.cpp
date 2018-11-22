#include "vox_material.hpp"

#include <cstring>

VoxMaterial::VoxMaterial(Type type)
    : id(0),
    type(type),
    weight(1.0f)
{
    for (int i = 0; i < 7; i++)
    {
        property_bits[i] = false;
        property_values[i] = 0.f;
    }
}

void VoxMaterial::set_property(Property property, bool value)
{
    property_bits[static_cast<int>(property)] = value;
}
