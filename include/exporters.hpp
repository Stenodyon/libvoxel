#ifndef EXPORTERS_HPP_
#define EXPORTERS_HPP_

#include <cstdint>
#include <string>

#include "node.hpp"
#include "box_area.hpp"
#include "vox_palette.hpp"

//void export_obj(Node<?> *root, BoxArea area, const std::string &filename);
void export_vox_shape(
        Node<bool> *root,
        const BoxArea &area,
        const std::string &filename);

void export_vox_color(
        Node<uint8_t> *root,
        const VoxPalette *palette,
        const BoxArea &area,
        const std::string &filename);

void export_vox(
        Node<uint8_t> *root,
        const VoxPalette *palette,
        const BoxArea &area,
        const std::string &filename);

#endif // EXPORTERS_HPP_
