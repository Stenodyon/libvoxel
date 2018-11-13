#include <gtest/gtest.h>

#include "utils.hpp"
#include "nodes/solid_node.hpp"

class SolidNodeTest : public ::testing::Test {};

TEST_F(SolidNodeTest, bool_false)
{
    auto node = SolidNode<bool>{false};
    bool got = node.get_voxel(random_point());
    ASSERT_EQ(got, false);
}

TEST_F(SolidNodeTest, bool_true)
{
    auto node = SolidNode<bool>{true};
    bool got = node.get_voxel(random_point());
    ASSERT_EQ(got, true);
}

TEST_F(SolidNodeTest, random_int)
{
    int value = randint();
    auto node = SolidNode<int>{value};
    int got = node.get_voxel(random_point());
    ASSERT_EQ(value, got);
}

TEST_F(SolidNodeTest, reference_address)
{
    int value = randint();
    auto node = SolidNode<int&>{value};
    int & got = node.get_voxel(random_point());
    ASSERT_EQ(&value, &got);
}
