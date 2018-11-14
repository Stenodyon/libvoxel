#include <gtest/gtest.h>

#include "utils.hpp"
#include "nodes/and_node.hpp"
#include "nodes/solid_node.hpp"

class ANDNodeTest : public ::testing::Test {};

TEST_F(ANDNodeTest, false_false)
{
    auto in1 = SolidNode<bool>{false};
    auto in2 = SolidNode<bool>{false};
    auto node = ANDNode{&in1, &in2};
    bool got = node.get_voxel(random_point());
    ASSERT_EQ(got, false);
}

TEST_F(ANDNodeTest, false_true)
{
    auto in1 = SolidNode<bool>{true};
    auto in2 = SolidNode<bool>{false};
    auto node = ANDNode{&in1, &in2};
    bool got = node.get_voxel(random_point());
    ASSERT_EQ(got, false);
}

TEST_F(ANDNodeTest, true_false)
{
    auto in1 = SolidNode<bool>{false};
    auto in2 = SolidNode<bool>{true};
    auto node = ANDNode{&in1, &in2};
    bool got = node.get_voxel(random_point());
    ASSERT_EQ(got, false);
}

TEST_F(ANDNodeTest, true_true)
{
    auto in1 = SolidNode<bool>{true};
    auto in2 = SolidNode<bool>{true};
    auto node = ANDNode{&in1, &in2};
    bool got = node.get_voxel(random_point());
    ASSERT_EQ(got, true);
}
