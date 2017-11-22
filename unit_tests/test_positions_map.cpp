#include "gtest\gtest.h"
#include "positions_map.h"

static const string reference(" <x><y> <x|y>x ");

TEST( constructor___operator_item_access, string_constructor ) {
    Positions_Map posmap(reference);
    EXPECT_EQ(posmap[0].right, '<');
}

TEST( constructor___operator_item_access, copy_constructor ) {
    Positions_Map posmap_1(reference);
    Positions_Map posmap_2(posmap_1);
    EXPECT_EQ(posmap_2[4].right, 'y');
}

TEST( begin___end___size, iterative_bypass ) {
    Positions_Map posmap(reference);
    bool flag = true;
    for (int i = 0; i < posmap.size(); ++i)
        flag = flag && (posmap[i].right == reference[i+1]);
    EXPECT_TRUE(flag);
}
