#include <unordered_set>
#include <unordered_map>

#include <gtest/gtest.h>

#include "point.hpp"

class PointTest : public ::testing::Test {};

TEST_F(PointTest, point_set)
{
    std::unordered_set<Point> set;
    EXPECT_EQ(set.size(), 0);
    set.insert({0, 0, 0});
    EXPECT_EQ(set.size(), 1);
    set.insert({1, 0, 0});
    EXPECT_EQ(set.size(), 2);
    set.insert({0, 0, 0});
    EXPECT_EQ(set.size(), 2);
}

TEST_F(PointTest, map_lookup)
{
    std::unordered_map<Point, int> map;
    EXPECT_EQ(map.find({0, 0, 0}), map.end());
    map.insert({{0, 0, 0}, 2});
    EXPECT_NE(map.find({0, 0, 0}), map.end());
}
