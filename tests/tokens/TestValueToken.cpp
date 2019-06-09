#include <CppUTest/TestHarness.h>

#include "ValueToken.h"

SimpleString StringFrom(const long double x) {
    return std::to_string(x).c_str();
}

#define LONGDBL_EQUAL(X, Y) CHECK_EQUAL(X, Y)

TEST_GROUP(TestValueTokens){

};

TEST(TestValueTokens, CanGetValueOfIntegerTokensAfterCreation) {
    refactor::IntegerToken tokenA{20};
    LONGS_EQUAL(20, tokenA.getValue());

    refactor::IntegerToken tokenB{-5};
    LONGS_EQUAL(-5, tokenB.getValue());
}

TEST(TestValueTokens, CanGetValueOfFloatPtTokensAfterCreation) {
    refactor::FloatPtToken tokenA{1.0};
    LONGDBL_EQUAL(1.0L, tokenA.getValue());

    refactor::FloatPtToken tokenB{-1.2e10};
    LONGDBL_EQUAL(-1.2e10L, tokenB.getValue());

    refactor::FloatPtToken tokenC{std::numeric_limits<long double>::infinity()};
    LONGDBL_EQUAL(std::numeric_limits<long double>::infinity(),
                  tokenC.getValue());
}