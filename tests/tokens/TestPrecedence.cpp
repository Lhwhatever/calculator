#include "gtest/gtest.h"

#include "calculator/Precedence.h"

namespace {
using refactor::Precedence;
}  // namespace

TEST(UnitTestForPrecedence, PrecedenceWithDiffNominalLvlAreUnequal) {
    EXPECT_NE(Precedence::l2r(1), Precedence::l2r(2));
    EXPECT_NE(Precedence::r2l(1), Precedence::r2l(2));
    EXPECT_NE(Precedence::l2r(1), Precedence::r2l(2));
    EXPECT_NE(Precedence::r2l(1), Precedence::l2r(2));
}

TEST(UnitTestForPrecedence, PrecedenceWithDiffAssocAreUnequal) {
    EXPECT_NE(Precedence::l2r(1), Precedence::r2l(2));
    EXPECT_NE(Precedence::l2r(2), Precedence::r2l(1));
    EXPECT_NE(Precedence::l2r(1), Precedence::r2l(1));
}

TEST(UnitTestForPrecedence,
     WhenAssocSamePrecedenceWithBiggerNominalLvlIsGreater) {
    EXPECT_GT(Precedence::l2r(2), Precedence::l2r(1));
    EXPECT_LT(Precedence::l2r(1), Precedence::l2r(2));
    EXPECT_GT(Precedence::r2l(2), Precedence::r2l(1));
    EXPECT_LT(Precedence::r2l(1), Precedence::r2l(2));
    EXPECT_GT(Precedence::l2r(2), Precedence::r2l(1));
    EXPECT_LT(Precedence::l2r(1), Precedence::r2l(2));
}

TEST(UnitTestForPrecedence, WhenNominalLvlSamePrecedenceWithL2RAssocGreater) {
    EXPECT_GT(Precedence::l2r(1), Precedence::r2l(1));
    EXPECT_LT(Precedence::r2l(1), Precedence::l2r(1));
}

TEST(UnitTestForPrecedence,
     PrecedenceWithBiggerNominalLvlOrSameLvlGTEAssocIsGTE) {
    EXPECT_GE(Precedence::l2r(1), Precedence::l2r(1));
    EXPECT_GE(Precedence::r2l(2), Precedence::l2r(1));
    EXPECT_GE(Precedence::l2r(2), Precedence::l2r(1));

    EXPECT_GE(Precedence::r2l(1), Precedence::r2l(1));
    EXPECT_GE(Precedence::l2r(1), Precedence::r2l(1));
    EXPECT_GE(Precedence::r2l(2), Precedence::r2l(1));
    EXPECT_GE(Precedence::l2r(2), Precedence::r2l(1));
}

TEST(UnitTestForPrecedence,
     PrecedenceWithBiggerNominalLvlOrSameLvlLTEAssocIsLTE) {
    EXPECT_LE(Precedence::r2l(1), Precedence::r2l(1));
    EXPECT_LE(Precedence::l2r(0), Precedence::l2r(1));
    EXPECT_LE(Precedence::r2l(0), Precedence::l2r(1));

    EXPECT_LE(Precedence::l2r(1), Precedence::l2r(1));
    EXPECT_LE(Precedence::r2l(1), Precedence::l2r(1));
    EXPECT_LE(Precedence::l2r(0), Precedence::l2r(1));
    EXPECT_LE(Precedence::r2l(0), Precedence::l2r(1));
}