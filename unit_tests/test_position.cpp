#include "gtest\gtest.h"
#include "position.h"

TEST( add_index_AND_get_indexes, _ ) {
    Position position(Position::MOCK, 'a');
    bool flag = true;

    flag *= !(position.get_indexes().has_item(42));
    position.add_index(42);
    flag *= (position.get_indexes().has_item(42));

    EXPECT_TRUE(flag);
}

TEST( is_before_left_bracket, _ ) {
    Position pos_1('a', '(');
    Position pos_2('a', '<');
    EXPECT_TRUE(pos_1.is_before_left_bracket() && pos_2.is_before_left_bracket());
}

TEST( is_before_left_iter_bracket, _ ) {
    Position pos('a','<');
    EXPECT_TRUE(pos.is_before_left_iter_bracket());
}

TEST( is_after_right_bracket, _ ) {
    Position pos_1(')', 'a');
    Position pos_2('>', 'a');
    EXPECT_TRUE(pos_1.is_after_right_bracket() && pos_2.is_after_right_bracket());
}

TEST( is_after_right_iter_bracket, _ ) {
    Position pos('>', 'a');
    EXPECT_TRUE(pos.is_after_right_iter_bracket());
}

TEST( is_before_term, _ ) {
    Position pos_1('a','b');
    Position pos_2('<', 'b');
    EXPECT_TRUE(!(pos_1.is_before_term()) && pos_2.is_before_term());
}

TEST( is_after_term, _ ) {
    Position pos_1('a','b');
    Position pos_2('b', '>');
    EXPECT_TRUE(!(pos_1.is_after_term()) && pos_2.is_after_term());
}

TEST( is_prebase, _ ) {
    Position pos_1('a', '<');
    Position pos_2('|', 'a');
    EXPECT_TRUE(!(pos_1.is_prebase()) && pos_2.is_prebase());
}

TEST( is_base, _ ) {
    Position pos_1('a', '>');
    Position pos_2('<','a');
    EXPECT_TRUE(pos_1.is_base() && !(pos_2.is_base()));
}

TEST( is_start, _ ) {
    Position pos_1(Position::MOCK, 'a');
    Position pos_2('a', Position::MOCK);
    EXPECT_TRUE(pos_1.is_start() && !(pos_2.is_start()));
}

TEST( is_end, _ ) {
    Position pos_1('a', Position::MOCK);
    Position pos_2(Position::MOCK, 'a' );
    EXPECT_TRUE(pos_1.is_end() && !(pos_2.is_end()));
}

TEST( is_special_char, _ ) {
    EXPECT_TRUE(Position::is_special_char('<') &&
        Position::is_special_char('(') &&
        Position::is_special_char(')') &&
        Position::is_special_char('>') &&
        Position::is_special_char('|') &&
        Position::is_special_char(Position::MOCK));
}
