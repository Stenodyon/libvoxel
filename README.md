# libvoxel
Small node-based voxel generation library (name is temporary).

## Example

```cpp
#include <libvoxel.hpp>

// You can define custom nodes, which must derive from Node and implement
// get_voxel(const Point &pos)
class LTNode : public Node<bool>
{
    private:
        Node<double> *input;
        double threshold;

    public:
        LTNode(Node<double> *input, double threshold)
            : input(input), threshold(threshold) {}

        bool get_voxel(const Point &pos) override {
            return input->get_voxel(pos) < threshold;
        }
};

int main()
{
    // Defining a 101x101x101 box to render
    auto area = BoxArea{{0, 0, 0}, {100, 100, 100}};

    // Defining the node graph
    //   [Perlin] -> [< 0.35] -> OBJ
    //
    // Graph is a container for nodes. It allows contiguous storage of nodes.
    auto graph = Graph();

    // PerlinNode(seed, octave)
    auto perlin = graph.add<PerlinNode>(42, 5);
    // LTNode defined above
    auto root = graph.add<LTNode>(perlin, 0.35);

    // The OBJ exporter takes a bool node as an input and generates an OBJ
    export_obj_shape(root, area, "example.obj");
    return 0;
}
```
