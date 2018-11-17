#include <gtest/gtest.h>

#include "utils.hpp"
#include "point.hpp"
#include "node.hpp"
#include "nodes/buffer_node.hpp"
#include "nodes/solid_node.hpp"

class BufferNodeTest : public ::testing::Test {};

class CountNode : public Node<bool>
{
    private:
        int counter;

    public:
        CountNode() : counter(0) {}

        bool get_voxel(const Point &pos) override {
            counter++;
            return false;
        }

        int get_counter() const { return counter; }
};

TEST_F(BufferNodeTest, proper_call_count)
{
    auto counter = CountNode();
    auto node = BufferNode<bool>{&counter};
    ASSERT_EQ(counter.get_counter(), 0);
    Point pt = random_point();
    node.get_voxel(pt);
    ASSERT_EQ(counter.get_counter(), 1);
    node.get_voxel(pt);
    ASSERT_EQ(counter.get_counter(), 1);
    node.get_voxel(pt + Point{1, 1, 1});
    ASSERT_EQ(counter.get_counter(), 2);
}

TEST_F(BufferNodeTest, proper_return_value)
{
    int value = randint();
    auto source = SolidNode<int>{value};
    auto node = BufferNode<int>{&source};
    Point pt = random_point();
    ASSERT_EQ(node.get_voxel(pt), value);
    ASSERT_EQ(node.get_voxel(pt), value);
}
