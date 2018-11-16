#include <gtest/gtest.h>

#include "utils.hpp"
#include "nodes/box_node.hpp"

class BoxNodeTest : public ::testing::Test {};

TEST_F(BoxNodeTest, inside)
{
    int inside_val = 13;
    int outside_val = 42;
    auto box = BoxArea{
        {0, 0, 0},
        {1, 2, 3}
    };
    auto point = Point{1, 1, 1};
    auto node = BoxNode<int>{box, inside_val, outside_val};

    EXPECT_TRUE(box.contains(point)); // Just making sure
    ASSERT_EQ(node.get_voxel(point), inside_val);
}

TEST_F(BoxNodeTest, outside)
{
    int inside_val = 13;
    int outside_val = 42;
    auto box = BoxArea{
        {0, 0, 0},
        {1, 2, 3}
    };
    auto point = Point{-1, 1, 1};
    auto node = BoxNode<int>{box, inside_val, outside_val};

    EXPECT_FALSE(box.contains(point)); // Just making sure
    ASSERT_EQ(node.get_voxel(point), outside_val);
}

TEST_F(BoxNodeTest, random)
{
    for (int i = 0; i < 256; i++)
    {
        int inside_val = 13;
        int outside_val = 42;
        auto box = BoxArea{
            random_point(),
            random_point()
        };
        auto point = random_point();
        auto node = BoxNode<int>{box, inside_val, outside_val};
        if (box.contains(point))
            ASSERT_EQ(node.get_voxel(point), inside_val);
        else
            ASSERT_EQ(node.get_voxel(point), outside_val);
    }
}
