#include "gtest\gtest.h"
#include "machine_matrix.h"
#include <iostream>

using namespace std;

static const string reference_1("_nm(c|d)<k>n<n|m>_");
static const string reference_2("_(<x|c>|n)(b|d)<a|k>y_");

TEST( markup_base_indexes, check_result ) {
    Positions_Map positions(reference_1);
    Machine_Matrix matrix(reference_1);
    bool flag = true;

    flag *= (matrix.m_posmap[0].get_indexes().get_integers().front() == 0);
    flag *= (matrix.m_posmap[1].get_indexes().get_integers().front() == 1);
    flag *= (matrix.m_posmap[2].get_indexes().get_integers().front() == 2);
    flag *= (matrix.m_posmap[4].get_indexes().get_integers().front() == 3);
    flag *= (matrix.m_posmap[6].get_indexes().get_integers().front() == 4);
    flag *= (matrix.m_posmap[9].get_indexes().get_integers().front() == 5);
    flag *= (matrix.m_posmap[11].get_indexes().get_integers().front() == 6);
    flag *= (matrix.m_posmap[13].get_indexes().get_integers().front() == 7);
    flag *= (matrix.m_posmap[15].get_indexes().get_integers().front() == 8);

    EXPECT_TRUE(flag);
}

void print_state(const Int_Set& state) {
    const list<int>& listint = state.get_integers();
    for (auto it = listint.begin(); it != listint.end(); ++it)
        cout << *it;
}
TEST( MANUAL_DEBUG, print_table ) {
    // _nm(c|d)<k>n<n|m>_"
    Positions_Map posmap(reference_1);
    Machine_Matrix matrix(posmap);

    const list<Int_Set>& states = matrix.get_states();
    const list<char>& symbols = matrix.get_symbols();
    cout << '\t';
    for (auto it = states.begin(); it != states.end(); ++it) {
        print_state(*it);
        cout << '\t';
    }
    cout << endl;
    for (auto it = symbols.begin(); it != symbols.end(); ++it) {
        cout << *it << '\t';
        for (auto init = states.begin(); init != states.end(); ++init) {
            print_state(matrix.get_cell(*it,*init));
            cout << '\t';
        }
        cout << endl;
    }
}

TEST( is_inside_nested_brackets, _ ) {
    Positions_Map positions_map(reference_1);
    Machine_Matrix matrix(positions_map);
    auto it_left_bracket = matrix.m_posmap.begin();
    auto it_inner_position = matrix.m_posmap.begin();
    bool flag = false;

    // (c|d)
    it_left_bracket++;
    it_left_bracket++;
    it_inner_position = it_left_bracket;
    it_inner_position++;
    flag = flag || (matrix.is_inside_nested_brackets(it_left_bracket, it_inner_position));
    it_inner_position++;
    flag = flag || (matrix.is_inside_nested_brackets(it_left_bracket, it_inner_position));
    it_inner_position++;
    flag = flag || (matrix.is_inside_nested_brackets(it_left_bracket, it_inner_position));
    it_inner_position++;
    flag = flag || (matrix.is_inside_nested_brackets(it_left_bracket, it_inner_position));

    // <k>
    it_left_bracket++;
    it_left_bracket++;
    it_left_bracket++;
    it_left_bracket++;
    it_left_bracket++;
    it_inner_position = it_left_bracket;
    it_inner_position++;
    flag = flag || (matrix.is_inside_nested_brackets(it_left_bracket, it_inner_position));
    flag = flag || (matrix.is_inside_nested_brackets(it_left_bracket, it_inner_position));
    flag = flag || (matrix.is_inside_nested_brackets(it_left_bracket, it_inner_position));

    // <n|m>
    it_left_bracket++;
    it_left_bracket++;
    it_left_bracket++;
    it_left_bracket++;
    it_inner_position = it_left_bracket;
    it_inner_position++;
    flag = flag || (matrix.is_inside_nested_brackets(it_left_bracket, it_inner_position));
    it_inner_position++;
    flag = flag || (matrix.is_inside_nested_brackets(it_left_bracket, it_inner_position));
    it_inner_position++;
    flag = flag || (matrix.is_inside_nested_brackets(it_left_bracket, it_inner_position));
    it_inner_position++;
    flag = flag || (matrix.is_inside_nested_brackets(it_left_bracket, it_inner_position));
    it_inner_position++;
    flag = flag || (matrix.is_inside_nested_brackets(it_left_bracket, it_inner_position));

    EXPECT_FALSE(flag);
}

TEST( seek_right_bracket, _ ) {
    Positions_Map positions_map(reference_1);
    Machine_Matrix matrix(positions_map);
    auto it_left_bracket = matrix.m_posmap.begin();
    bool flag = true;

    // (c|d)
    for (int i = 0; i < 2; i++) it_left_bracket++;
    flag = flag && (matrix.seek_right_bracket(it_left_bracket)->left == ')');

    // <k>
    for (int i = 0; i < 5; i++) it_left_bracket++;
    flag = flag && (matrix.seek_right_bracket(it_left_bracket)->left == '>');

    // <n|m>
    for (int i = 0; i < 4; i++) it_left_bracket++;
    flag = flag && (matrix.seek_right_bracket(it_left_bracket)->left == '>');

    EXPECT_TRUE(flag);
}


//
//
//
//
//
//
//
