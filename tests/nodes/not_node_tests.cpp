#include <gtest/gtest.h>

#include "utils.hpp"
#include "nodes/solid_node.hpp"
#include "nodes/not_node.hpp"

class NOTNodeTest : public ::testing::Test {};

TEST_F(NOTNodeTest, not_false)
{
    auto solid = SolidNode<bool>{false};
    auto node = NOTNode{&solid};
    bool got = node.get_voxel(random_point());
    ASSERT_EQ(got, true);
}

TEST_F(NOTNodeTest, not_true)
{
    auto solid = SolidNode<bool>{true};
    auto node = NOTNode{&solid};
    bool got = node.get_voxel(random_point());
    ASSERT_EQ(got, false);
}
