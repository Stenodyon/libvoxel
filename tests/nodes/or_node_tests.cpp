#include <gtest/gtest.h>

#include "utils.hpp"
#include "nodes/or_node.hpp"
#include "nodes/solid_node.hpp"

class ORNodeTest : public ::testing::Test {};

TEST_F(ORNodeTest, false_false)
{
    auto in1 = SolidNode<bool>{false};
    auto in2 = SolidNode<bool>{false};
    auto node = ORNode{&in1, &in2};
    bool got = node.get_voxel(random_point());
    ASSERT_EQ(got, false);
}

TEST_F(ORNodeTest, false_true)
{
    auto in1 = SolidNode<bool>{true};
    auto in2 = SolidNode<bool>{false};
    auto node = ORNode{&in1, &in2};
    bool got = node.get_voxel(random_point());
    ASSERT_EQ(got, true);
}

TEST_F(ORNodeTest, true_false)
{
    auto in1 = SolidNode<bool>{false};
    auto in2 = SolidNode<bool>{true};
    auto node = ORNode{&in1, &in2};
    bool got = node.get_voxel(random_point());
    ASSERT_EQ(got, true);
}

TEST_F(ORNodeTest, true_true)
{
    auto in1 = SolidNode<bool>{true};
    auto in2 = SolidNode<bool>{true};
    auto node = ORNode{&in1, &in2};
    bool got = node.get_voxel(random_point());
    ASSERT_EQ(got, true);
}
