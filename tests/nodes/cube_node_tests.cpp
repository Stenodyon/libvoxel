#include <gtest/gtest.h>

#include "utils.hpp"
#include "nodes/cube_node.hpp"

class CubeNodeTests : public ::testing::Test {};

TEST_F(CubeNodeTests, test_0)
{
    int inside_val = 13;
    int outside_val = 42;
    auto node = CubeNode<int>{0, inside_val, outside_val};
    EXPECT_EQ(node.get_voxel({0, 0, 0}), inside_val);
    EXPECT_EQ(node.get_voxel({1, 0, 0}), outside_val);
    EXPECT_EQ(node.get_voxel({0, 1, 0}), outside_val);
    EXPECT_EQ(node.get_voxel({0, 0, 1}), outside_val);
}

TEST_F(CubeNodeTests, test_3)
{
    int inside_val = 13;
    int outside_val = 42;
    auto node = CubeNode<int>{3, inside_val, outside_val};
    for (int p = 0; p <= 3; p++)
    {
        EXPECT_EQ(node.get_voxel({p, 0, 0}), inside_val);
        EXPECT_EQ(node.get_voxel({0, p, 0}), inside_val);
        EXPECT_EQ(node.get_voxel({0, 0, p}), inside_val);
        EXPECT_EQ(node.get_voxel({-p, 0, 0}), inside_val);
        EXPECT_EQ(node.get_voxel({0, -p, 0}), inside_val);
        EXPECT_EQ(node.get_voxel({0, 0, -p}), inside_val);
    }
    EXPECT_EQ(node.get_voxel({4, 0, 0}), outside_val);
    EXPECT_EQ(node.get_voxel({0, 4, 0}), outside_val);
    EXPECT_EQ(node.get_voxel({0, 0, 4}), outside_val);
    EXPECT_EQ(node.get_voxel({-4, 0, 0}), outside_val);
    EXPECT_EQ(node.get_voxel({0, -4, 0}), outside_val);
    EXPECT_EQ(node.get_voxel({0, 0, -4}), outside_val);
}
