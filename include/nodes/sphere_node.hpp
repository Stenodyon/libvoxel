#ifndef SPHERE_NODE_HPP_
#define SPHERE_NODE_HPP_

template <typename T>
class SphereNode : public Node<T>
{
    private:
        double radius_sq;
        T inside, outside;

    public:
        SphereNode(double radius, T inside, T outside);

        T get_voxel(const Point & pos) override;
};

template <typename T>
SphereNode<T>::SphereNode(double radius, T inside, T outside)
    : radius_sq(radius * radius), inside(inside), outside(outside)
{
}

template <typename T>
T SphereNode<T>::get_voxel(const Point & pos)
{
    if (pos.norm_sq() <= radius_sq)
        return inside;
    else
        return outside;
}

#endif // SPHERE_NODE_HPP_
