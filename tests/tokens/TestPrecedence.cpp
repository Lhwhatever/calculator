#include "gtest/gtest.h"

#include "calculator/Precedence.h"

namespace {
using refactor::Precedence;
}  // namespace

TEST(UnitTestForPrecedence, PrecedenceWithDiffNominalLvlAreUnequal) {
    EXPECT_NE(1_l2r, 2_l2r);
    EXPECT_NE(1_r2l, 2_r2l);
    EXPECT_NE(1_l2r, 2_r2l);
    EXPECT_NE(1_r2l, 2_l2r);
}

TEST(UnitTestForPrecedence, PrecedenceWithDiffAssocAreUnequal) {
    EXPECT_NE(1_l2r, 2_r2l);
    EXPECT_NE(2_l2r, 1_r2l);
    EXPECT_NE(1_l2r, 1_r2l);
}

TEST(UnitTestForPrecedence,
     WhenAssocSamePrecedenceWithBiggerNominalLvlIsGreater) {
    EXPECT_GT(2_l2r, 1_l2r);
    EXPECT_LT(1_l2r, 2_l2r);
    EXPECT_GT(2_r2l, 1_r2l);
    EXPECT_LT(1_r2l, 2_r2l);
    EXPECT_GT(2_l2r, 1_r2l);
    EXPECT_LT(1_l2r, 2_r2l);
}

TEST(UnitTestForPrecedence, WhenNominalLvlSamePrecedenceWithL2RAssocGreater) {
    EXPECT_GT(1_l2r, 1_r2l);
    EXPECT_LT(1_r2l, 1_l2r);
}

TEST(UnitTestForPrecedence,
     PrecedenceWithBiggerNominalLvlOrSameLvlGTEAssocIsGTE) {
    EXPECT_GE(1_l2r, 1_l2r);
    EXPECT_GE(2_r2l, 1_l2r);
    EXPECT_GE(2_l2r, 1_l2r);

    EXPECT_GE(1_r2l, 1_r2l);
    EXPECT_GE(1_l2r, 1_r2l);
    EXPECT_GE(2_r2l, 1_r2l);
    EXPECT_GE(2_l2r, 1_r2l);
}

TEST(UnitTestForPrecedence,
     PrecedenceWithBiggerNominalLvlOrSameLvlLTEAssocIsLTE) {
    EXPECT_LE(1_r2l, 1_r2l);
    EXPECT_LE(0_l2r, 1_l2r);
    EXPECT_LE(0_r2l, 1_l2r);

    EXPECT_LE(1_l2r, 1_l2r);
    EXPECT_LE(1_r2l, 1_l2r);
    EXPECT_LE(0_l2r, 1_l2r);
    EXPECT_LE(0_r2l, 1_l2r);
}