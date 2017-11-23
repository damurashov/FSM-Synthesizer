#include "gtest\gtest.h"
#include "positions_map.h"
#include <iostream>

using namespace std;

static const string reference("_<x><y>_<x|y>x_");
static const string reference2("_<x><y>_");

TEST( MANUAL_DEBUG, _____ ) {
    Positions_Map posmap(reference2);
    for (auto it = posmap.begin(); it != posmap.end(); it++)
        cout << it->right;
    cout << endl;
}

TEST( constructor___operator_item_access, string_constructor ) {
    Positions_Map posmap(reference);
    EXPECT_EQ(posmap[0].right, '<');
}

TEST( constructor___operator_item_access, copy_constructor ) {
    Positions_Map posmap_1(reference);
    Positions_Map posmap_2(posmap_1);
    EXPECT_EQ(posmap_2[4].right, 'y');
    for (auto it = posmap_2.begin(); it != posmap_2.end(); ++it)
        cout << it->right;
    cout << endl;
}

TEST( begin___end, iterative_bypass ) {
    Positions_Map posmap(reference);
    for (auto it = posmap.begin(); it != posmap.end(); ++it)
        cout << it->right << endl;
}
