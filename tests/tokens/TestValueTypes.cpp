#include "gtest/gtest.h"

#include "calculator/ValueToken.h"

TEST(UnitTestForValueT, IntegerTokensAreAllowed) {
    EXPECT_TRUE(ValueTypes<ValueT::IntegerT>::ALLOWED);
}

TEST(UnitTestForValueT, RealNumTokensAreAllowed) {
    EXPECT_TRUE(ValueTypes<ValueT::RealNumT>::ALLOWED);
}

TEST(UnitTest_TestValueT, BoolTokensAreNotAllowed) {
    EXPECT_FALSE(ValueTypes<bool>::ALLOWED);
}