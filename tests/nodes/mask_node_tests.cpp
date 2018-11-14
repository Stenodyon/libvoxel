#include <gtest/gtest.h>

#include "utils.hpp"
#include "nodes/mask_node.hpp"
#include "nodes/solid_node.hpp"

class MaskNodeTest : public ::testing::Test {};

TEST_F(MaskNodeTest, inside_mask)
{
    auto default_value = 0;
    auto value = 42;
    auto input = SolidNode<int>{value};
    auto mask = SolidNode<bool>{true};
    auto node = MaskNode<int>{&input, &mask, default_value};
    int got = node.get_voxel(random_point());
    ASSERT_EQ(got, value);
}

TEST_F(MaskNodeTest, outside_mask)
{
    auto default_value = 0;
    auto value = 42;
    auto input = SolidNode<int>{value};
    auto mask = SolidNode<bool>{false};
    auto node = MaskNode<int>{&input, &mask, default_value};
    int got = node.get_voxel(random_point());
    ASSERT_EQ(got, default_value);
}

// TODO (cannot test the mask node with only SolidNodes)
