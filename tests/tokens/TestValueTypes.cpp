#include <CppUTest/TestHarness.h>

#include "ValueToken.h"

/** @ingroup unit_tests
 * @brief Tests the attributes of the different possible forms of
 * `ValueType<T>`.
 *
 */
TEST_GROUP(UnitTest_TestValueTypes){

};

TEST(UnitTest_TestValueTypes, IntegerTokensAreAllowed) {
    CHECK(ValueTypes<refactor::IntegerToken::type>::ALLOWED);
};

TEST(UnitTest_TestValueTypes, FloatPtTokensAreAllowed) {
    CHECK(ValueTypes<refactor::FloatPtToken::type>::ALLOWED);
}

TEST(UnitTest_TestValueTypes, BoolTokensAreNotAllowed) {
    CHECK(!ValueTypes<bool>::ALLOWED);
}