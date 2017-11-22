#include "gtest\gtest.h"
#include "int_set.h"

TEST( is_empty, _ ) {
    Int_Set intset;
    bool flag = true;

    flag *= intset.is_empty();
    intset.push(2);
    flag *= (!intset.is_empty());

    EXPECT_TRUE(flag);
}

TEST( has_intersections, _ ) {
    Int_Set reference;
    Int_Set intset_1; // Does have
    Int_Set intset_2; // Doesn't have

    for (int i = 0; i < 5; ++i) reference.push(i);
    for (int i = 4; i < 6; ++i) intset_1.push(i);
    for (int i = 5; i < 6; ++i) intset_2.push(i);

    EXPECT_TRUE(reference.has_intersections(intset_1) &&
        !(reference.has_intersections(intset_2)));
}

TEST( has_item, _ ) {
    Int_Set intset;

    for (int i = 0; i < 5; ++i) intset.push(i);
    EXPECT_TRUE(intset.has_item(4) && !intset.has_item(5));
}

TEST( operator_eq_eq, _ ) {
    Int_Set reference;
    Int_Set intset_1; // Is equal to the "reference"
    Int_Set intset_2; // Is not equal

    for (int i = 0; i < 5; ++i) reference.push(i);
    for (int i = 4; i >=0; --i) intset_1.push(i);
    for (int i = 5; i > 0; --i) intset_2.push(i);

    EXPECT_TRUE(reference == intset_1 && !(reference == intset_2) );
}

TEST( append, _ ) {
    Int_Set intset_1;
    Int_Set intset_2;

    for (int i = 0; i < 5; ++i) intset_1.push(i);
    for (int i = 3; i < 9; ++i) intset_2.push(i);
    intset_1.append(intset_2);

    EXPECT_TRUE(intset_1.has_item(0) &&
        intset_1.has_item(7) &&
        !intset_2.has_item(2));
}

TEST( push, _ ) {
    Int_Set intset;
    bool flag = true;

    flag *= !intset.has_item(42);
    intset.push(42);
    flag *= intset.has_item(42);

    EXPECT_TRUE(flag);
}

TEST( operator_eq, _ ) {
    Int_Set reference;
    Int_Set intset;

    for (int i = 0; i < 10; ++i) reference.push(i);
    intset = reference;
    EXPECT_TRUE(reference.has_item(4));
}
