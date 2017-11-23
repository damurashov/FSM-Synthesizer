#include "gtest\gtest.h"
#include "machine_matrix.h"
#include <iostream>

using namespace std;

static const string reference("_<ab<c|d><ef>d>_");
static const string reference2("_<a|b|c>_");
static const string reference3("_<ab<c|d<f|g>>e>_");

TEST( is_inside_nested_brackets, there_is_no_nested_brackets ) {
    Positions_Map posmap(reference2);
    Machine_Matrix matrix(posmap);

    for (auto it = posmap.begin(); it != posmap.end(); ++it )
        if (it->right==Position::MOCK)
            cout << "YAHOOO!" << endl;
    cout << posmap.end()->right;
    auto it_1 = matrix.m_posmap.begin();
    auto it_2 = matrix.m_posmap.begin();
    it_2++; it_2++;
    EXPECT_FALSE(matrix.is_inside_nested_brackets(it_1, it_2));
}

TEST( is_inside_nested_brackets, is_not_inside ) {
    Positions_Map posmap(reference3);
    auto itr = posmap.begin();
    cout << '[' << itr->left;
    for (auto it = posmap.begin(); it != posmap.end(); ++it)
        cout << it->right;
    cout << ']' << endl;
    Machine_Matrix matrix(posmap);
    Positions_Map::Iterator it_1 = matrix.m_posmap.begin();
    Positions_Map::Iterator it_2 = matrix.m_posmap.begin();
    for (int i = 0; i < 13; i++) it_2++;
    EXPECT_FALSE(matrix.is_inside_nested_brackets(it_1, it_2));
}

TEST( is_inside_nested_brackets, is_inside ) {
    Positions_Map posmap(reference);
    Positions_Map posmap_2(posmap);
    for (auto it = posmap_2.begin(); it != posmap_2.end(); ++it)
        cout << it->right;
    cout << endl;
    Machine_Matrix matrix(posmap);
    Positions_Map::Iterator it_1 = matrix.m_posmap.begin();
    Positions_Map::Iterator it_2 = matrix.m_posmap.begin();
    for (int i = 0; i < 7; i++) it_2++;
    for (auto it = matrix.m_posmap.begin(); it != matrix.m_posmap.end(); ++it)
        if (it == matrix.m_posmap.begin())
            cout << '[' << it->left << it->right;
        else
            cout << it->right;
    cout << ']' << endl;
    EXPECT_TRUE(matrix.is_inside_nested_brackets(it_1, it_2));
}


//
//
//
//
//
//
//
