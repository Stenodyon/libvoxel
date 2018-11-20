#include <gtest/gtest.h>

#include "utils.hpp"
#include "box_area.hpp"

class BoxAreaTest : public ::testing::Test {};

TEST_F(BoxAreaTest, lower_corner1)
{
    auto box = BoxArea{
        Point{1, 2, 3},
        Point{3, 4, 5}
    };
    auto lower_corner = box.lower_corner();
    EXPECT_EQ(lower_corner[0], 1);
    EXPECT_EQ(lower_corner[1], 2);
    EXPECT_EQ(lower_corner[2], 3);
}

TEST_F(BoxAreaTest, lower_corner2)
{
    auto box = BoxArea{
        Point{1, 4, 3},
        Point{3, 2, 5}
    };
    auto lower_corner = box.lower_corner();
    EXPECT_EQ(lower_corner[0], 1);
    EXPECT_EQ(lower_corner[1], 2);
    EXPECT_EQ(lower_corner[2], 3);
}

TEST_F(BoxAreaTest, lower_corner3)
{
    auto box = BoxArea{
        Point{3, 2, 5},
        Point{1, 4, 3}
    };
    auto lower_corner = box.lower_corner();
    EXPECT_EQ(lower_corner[0], 1);
    EXPECT_EQ(lower_corner[1], 2);
    EXPECT_EQ(lower_corner[2], 3);
}

TEST_F(BoxAreaTest, upper_corner1)
{
    auto box = BoxArea{
        Point{1, 2, 3},
        Point{3, 4, 5}
    };
    auto upper_corner = box.upper_corner();
    EXPECT_EQ(upper_corner[0], 3);
    EXPECT_EQ(upper_corner[1], 4);
    EXPECT_EQ(upper_corner[2], 5);
}

TEST_F(BoxAreaTest, upper_corner2)
{
    auto box = BoxArea{
        Point{1, 4, 3},
        Point{3, 2, 5}
    };
    auto upper_corner = box.upper_corner();
    EXPECT_EQ(upper_corner[0], 3);
    EXPECT_EQ(upper_corner[1], 4);
    EXPECT_EQ(upper_corner[2], 5);
}

TEST_F(BoxAreaTest, upper_corner3)
{
    auto box = BoxArea{
        Point{3, 2, 5},
        Point{1, 4, 3}
    };
    auto upper_corner = box.upper_corner();
    EXPECT_EQ(upper_corner[0], 3);
    EXPECT_EQ(upper_corner[1], 4);
    EXPECT_EQ(upper_corner[2], 5);
}

TEST_F(BoxAreaTest, size_1)
{
    const auto loc = random_point();
    auto box = BoxArea{loc, loc};
    EXPECT_EQ(box.size_x(), 1);
    EXPECT_EQ(box.size_y(), 1);
    EXPECT_EQ(box.size_z(), 1);
}

TEST_F(BoxAreaTest, size_2)
{
    auto box = BoxArea{
        Point{0, 0, 0},
        Point{3, 4, 5}
    };
    EXPECT_EQ(box.size_x(), 4);
    EXPECT_EQ(box.size_y(), 5);
    EXPECT_EQ(box.size_z(), 6);
}

TEST_F(BoxAreaTest, size_3)
{
    auto box = BoxArea{
        Point{3, 4, 5},
        Point{1, 2, 3}
    };
    EXPECT_EQ(box.size_x(), 3);
    EXPECT_EQ(box.size_y(), 3);
    EXPECT_EQ(box.size_z(), 3);
}

TEST_F(BoxAreaTest, voxel_count1)
{
    auto box = BoxArea{
        {0, 0, 0},
        {1, 2, 3}
    };
    ASSERT_EQ(box.voxel_count(), 2 * 3 * 4);
}

TEST_F(BoxAreaTest, voxel_count2)
{
    auto box = BoxArea{
        {0, 0, 0},
        {5, 42, 77}
    };
    ASSERT_EQ(box.voxel_count(), 6 * 43 * 78);
}

TEST_F(BoxAreaTest, face_xl)
{
    auto box = BoxArea{
        random_point(),
        random_point()
    };
    auto face_xl = box.face_xl();

    EXPECT_EQ(face_xl.lower_corner()[0], box.lower_corner()[0]);
    EXPECT_EQ(face_xl.upper_corner()[0], box.lower_corner()[0]);

    EXPECT_EQ(face_xl.lower_corner()[1], box.lower_corner()[1]);
    EXPECT_EQ(face_xl.upper_corner()[1], box.upper_corner()[1]);

    EXPECT_EQ(face_xl.lower_corner()[2], box.lower_corner()[2]);
    EXPECT_EQ(face_xl.upper_corner()[2], box.upper_corner()[2]);
}

TEST_F(BoxAreaTest, face_xu)
{
    auto box = BoxArea{
        random_point(),
        random_point()
    };
    auto face_xu = box.face_xu();

    EXPECT_EQ(face_xu.lower_corner()[0], box.upper_corner()[0]);
    EXPECT_EQ(face_xu.upper_corner()[0], box.upper_corner()[0]);

    EXPECT_EQ(face_xu.lower_corner()[1], box.lower_corner()[1]);
    EXPECT_EQ(face_xu.upper_corner()[1], box.upper_corner()[1]);

    EXPECT_EQ(face_xu.lower_corner()[2], box.lower_corner()[2]);
    EXPECT_EQ(face_xu.upper_corner()[2], box.upper_corner()[2]);
}

TEST_F(BoxAreaTest, face_yl)
{
    auto box = BoxArea{
        random_point(),
        random_point()
    };
    auto face_yl = box.face_yl();

    EXPECT_EQ(face_yl.lower_corner()[0], box.lower_corner()[0]);
    EXPECT_EQ(face_yl.upper_corner()[0], box.upper_corner()[0]);

    EXPECT_EQ(face_yl.lower_corner()[1], box.lower_corner()[1]);
    EXPECT_EQ(face_yl.upper_corner()[1], box.lower_corner()[1]);

    EXPECT_EQ(face_yl.lower_corner()[2], box.lower_corner()[2]);
    EXPECT_EQ(face_yl.upper_corner()[2], box.upper_corner()[2]);
}

TEST_F(BoxAreaTest, face_yu)
{
    auto box = BoxArea{
        random_point(),
        random_point()
    };
    auto face_yu = box.face_yu();

    EXPECT_EQ(face_yu.lower_corner()[0], box.lower_corner()[0]);
    EXPECT_EQ(face_yu.upper_corner()[0], box.upper_corner()[0]);

    EXPECT_EQ(face_yu.lower_corner()[1], box.upper_corner()[1]);
    EXPECT_EQ(face_yu.upper_corner()[1], box.upper_corner()[1]);

    EXPECT_EQ(face_yu.lower_corner()[2], box.lower_corner()[2]);
    EXPECT_EQ(face_yu.upper_corner()[2], box.upper_corner()[2]);
}

TEST_F(BoxAreaTest, face_zl)
{
    auto box = BoxArea{
        random_point(),
        random_point()
    };
    auto face_zl = box.face_zl();

    EXPECT_EQ(face_zl.lower_corner()[0], box.lower_corner()[0]);
    EXPECT_EQ(face_zl.upper_corner()[0], box.upper_corner()[0]);

    EXPECT_EQ(face_zl.lower_corner()[1], box.lower_corner()[1]);
    EXPECT_EQ(face_zl.upper_corner()[1], box.upper_corner()[1]);

    EXPECT_EQ(face_zl.lower_corner()[2], box.lower_corner()[2]);
    EXPECT_EQ(face_zl.upper_corner()[2], box.lower_corner()[2]);
}

TEST_F(BoxAreaTest, face_zu)
{
    auto box = BoxArea{
        random_point(),
        random_point()
    };
    auto face_zu = box.face_zu();

    EXPECT_EQ(face_zu.lower_corner()[0], box.lower_corner()[0]);
    EXPECT_EQ(face_zu.upper_corner()[0], box.upper_corner()[0]);

    EXPECT_EQ(face_zu.lower_corner()[1], box.lower_corner()[1]);
    EXPECT_EQ(face_zu.upper_corner()[1], box.upper_corner()[1]);

    EXPECT_EQ(face_zu.lower_corner()[2], box.upper_corner()[2]);
    EXPECT_EQ(face_zu.upper_corner()[2], box.upper_corner()[2]);
}

TEST_F(BoxAreaTest, contains)
{
    auto box = BoxArea{
        {0, 0, 0},
        {1, 2, 3}
    };
    EXPECT_TRUE(box.contains(Point{0, 2, 0}));
    EXPECT_TRUE(box.contains(Point{1, 0, 3}));
    EXPECT_FALSE(box.contains(Point{-1, 0, 3}));
    EXPECT_FALSE(box.contains(Point{1, 2, 5}));
}

TEST_F(BoxAreaTest, outside)
{
    auto box = BoxArea{
        random_point(),
        random_point()
    };
    auto lower = box.lower_corner();
    auto upper = box.upper_corner();
    auto outside = box.outside(2);
    EXPECT_TRUE(box.contains(lower)); // Just checking
    EXPECT_TRUE(box.contains(upper)); // Just checking

    EXPECT_TRUE(outside.contains(lower));
    EXPECT_TRUE(outside.contains(lower - Point{2, 2, 2}));
    EXPECT_FALSE(outside.contains(lower - Point{3, 3, 3}));

    EXPECT_TRUE(outside.contains(upper));
    EXPECT_TRUE(outside.contains(upper + Point{2, 2, 2}));
    EXPECT_FALSE(outside.contains(upper + Point{3, 3, 3}));
}

TEST_F(BoxAreaTest, inside)
{
    auto box = BoxArea{
        random_point(),
        random_point()
    };
    auto lower = box.lower_corner();
    auto upper = box.upper_corner();
    auto inside = box.inside(2);
    EXPECT_TRUE(box.contains(lower)); // Just checking
    EXPECT_TRUE(box.contains(upper)); // Just checking

    EXPECT_FALSE(inside.contains(lower));
    EXPECT_FALSE(inside.contains(lower + Point{1, 1, 1}));
    EXPECT_TRUE(inside.contains(lower + Point{2, 2, 2}));

    EXPECT_FALSE(inside.contains(upper));
    EXPECT_FALSE(inside.contains(upper - Point{1, 1, 1}));
    EXPECT_TRUE(inside.contains(upper - Point{2, 2, 2}));
}

TEST_F(BoxAreaTest, dice1)
{
    auto box = BoxArea{
        {0, 0, 0},
        {1, 2, 3}
    };
    auto dices = box.dice(1, 1, 1);
    EXPECT_EQ(dices.size(), box.voxel_count());
}

TEST_F(BoxAreaTest, dice2)
{
    auto box = BoxArea{
        {0, 0, 0},
        {9, 9, 9}
    };
    {
        auto dices = box.dice(5, 5, 5);
        EXPECT_EQ(dices.size(), 8);
    }
    {
        auto dices = box.dice(4, 4, 4);
        EXPECT_EQ(dices.size(), 27);
    }
}

// ============================================================================
//   BoxArea::iterator
// ============================================================================

TEST_F(BoxAreaTest, iterator_count)
{
    auto corner = random_point();
    auto box = BoxArea{corner, corner + Point{1, 2, 3}};
    int counter = 0;
    for (auto point : box) counter++;
    EXPECT_EQ(box.size_x(), 2);
    EXPECT_EQ(box.size_y(), 3);
    EXPECT_EQ(box.size_z(), 4);
    ASSERT_EQ(counter, box.voxel_count());
}
