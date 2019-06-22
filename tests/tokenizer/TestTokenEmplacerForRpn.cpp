#include <memory>

#include "gtest/gtest.h"

#include "calculator/TokenEmplacerForRpn.h"
#include "calculator/ValueToken.h"

TEST(UnitTestForTokenEmplacerForRpn, ReturnsTokensInSequence) {
    TokenEmplacerForRpn emplacer;
    EXPECT_EQ(emplacer.extract(), TokenQueue{});
}
