#include "TestValueToken.cpp"
#include "ValueTokenFactory.h"

TEST(UnitTestForTokenFactories, WhenValidStringGivenCreateIntegerToken) {
    auto factory{std::make_unique<ValueTokenFactory<refactor::IntegerToken>>()};
    EXPECT_EQ(refactor::IntegerToken{10}, factory->create("10"));
}
