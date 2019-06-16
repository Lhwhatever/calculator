#include "gtest/gtest.h"

#include "calculator/ValueToken.h"

/** @ingroup unit_tests
 * @brief Tests the attributes of the different possible forms of
 * `ValueType<T>`.
 *
 */

TEST(UnitTestForValueTypes, IntegerTokensAreAllowed) {
    EXPECT_TRUE(ValueTypes<refactor::IntegerToken::type>::ALLOWED);
}

TEST(UnitTestForValueTypes, FloatPtTokensAreAllowed) {
    EXPECT_TRUE(ValueTypes<refactor::FloatPtToken::type>::ALLOWED);
}

TEST(UnitTest_TestValueTypes, BoolTokensAreNotAllowed) {
    EXPECT_FALSE(ValueTypes<bool>::ALLOWED);
}