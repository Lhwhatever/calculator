#include "gtest/gtest.h"

#include "calculator/ValueToken.h"

TEST(UnitTestForValueTokens, CanGetValueOfIntegerTokensAfterCreation) {
    refactor::IntegerToken tokenA{20};
    EXPECT_EQ(tokenA.getValue(), 20);

    refactor::IntegerToken tokenB{-5};
    EXPECT_EQ(tokenB.getValue(), -5);
}

TEST(TestValueTokens, CanGetValueOfFloatPtTokensAfterCreation) {
    refactor::FloatPtToken tokenA{1.0};
    EXPECT_EQ(tokenA.getValue(), 1.0L);

    refactor::FloatPtToken tokenB{-1.2e10};
    EXPECT_EQ(tokenB.getValue(), -1.2e10L);

    refactor::FloatPtToken tokenC{std::numeric_limits<long double>::infinity()};
    EXPECT_EQ(tokenC.getValue(), std::numeric_limits<long double>::infinity());
}