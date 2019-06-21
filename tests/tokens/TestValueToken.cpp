#include "gtest/gtest.h"

#include "calculator/ValueToken.h"

TEST(UnitTestForValueTokens, CanGetValueOfIntegerTokensAfterCreation) {
    refactor::IntegerToken tokenA{20};
    EXPECT_EQ(tokenA.value, 20);

    refactor::IntegerToken tokenB{-5};
    EXPECT_EQ(tokenB.value, -5);
}

TEST(TestValueTokens, CanGetValueOfFloatPtTokensAfterCreation) {
    refactor::FloatPtToken tokenA{1.0};
    EXPECT_EQ(tokenA.value, 1.0L);

    refactor::FloatPtToken tokenB{-1.2e10};
    EXPECT_EQ(tokenB.value, -1.2e10L);

    refactor::FloatPtToken tokenC{std::numeric_limits<long double>::infinity()};
    EXPECT_EQ(tokenC.value, std::numeric_limits<long double>::infinity());
}