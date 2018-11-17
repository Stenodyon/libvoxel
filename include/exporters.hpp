#ifndef EXPORTERS_HPP_
#define EXPORTERS_HPP_

#include <string>

#include "node.hpp"
#include "box_area.hpp"

//void export_obj(Node<?> *root, BoxArea area, const std::string &filename);
void export_vox_shape(
        Node<bool> *root,
        BoxArea area,
        const std::string &filename);

#endif // EXPORTERS_HPP_
