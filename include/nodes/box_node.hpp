#ifndef BOX_NODE_HPP_
#define BOX_NODE_HPP_

#include "node.hpp"
#include "point.hpp"
#include "box_area.hpp"

template <typename T>
class BoxNode : public Node<T>
{
    private:
        BoxArea box;
        T inside, outside;

    public:
        BoxNode(BoxArea box, T inside, T outside);

        T get_voxel(const Point & pos) override;
};

template <typename T>
BoxNode<T>::BoxNode(BoxArea box, T inside, T outside)
    : box(box), inside(inside), outside(outside)
{
}

template <typename T>
T BoxNode<T>::get_voxel(const Point & pos)
{
    return box.contains(pos) ? inside : outside;
}

#endif // BOX_NODE_HPP_
