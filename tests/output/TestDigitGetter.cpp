#include "gtest/gtest.h"

#include "calculator/DigitsGetter.h"

TEST(UnitTestForDigitGetter, GetFloatDigitsForFixedPtCorrectly) {
    EXPECT_EQ(digits::fixedPt::get(1.0L, 1), "1.0");
    EXPECT_EQ(digits::fixedPt::get(1.0L, 3), "1.000");
    EXPECT_EQ(digits::fixedPt::get(1.23L, 1), "1.2");
    EXPECT_EQ(digits::fixedPt::get(-1.23L, 1), "-1.2");
    EXPECT_EQ(digits::fixedPt::get(0.01L, 1), "0.0");
}

TEST(UnitTestForDigitGetter, GetFloatDigitsForFixedPtAutoPrecCorrectly) {
    EXPECT_EQ(digits::fixedPt::getWithAutoPrecision(1.21L, 2), "1.21");
    EXPECT_EQ(digits::fixedPt::getWithAutoPrecision(1.201L, 2), "1.201");
    EXPECT_EQ(digits::fixedPt::getWithAutoPrecision(1.2001L, 2), "1.2001");
    EXPECT_EQ(digits::fixedPt::getWithAutoPrecision(1.20001L, 2), "1.2");
    EXPECT_EQ(digits::fixedPt::getWithAutoPrecision(1.20001L, 3), "1.20001");
    EXPECT_EQ(digits::fixedPt::getWithAutoPrecision(1.0001L, 2), "1.0");
    EXPECT_EQ(digits::fixedPt::getWithAutoPrecision(-1.0001L, 2), "-1.0");
    EXPECT_EQ(digits::fixedPt::getWithAutoPrecision(1.91L, 2), "1.91");
    EXPECT_EQ(digits::fixedPt::getWithAutoPrecision(1.991L, 2), "1.991");
    EXPECT_EQ(digits::fixedPt::getWithAutoPrecision(1.9991L, 2), "2.0");
}

TEST(UnitTestForDigitGetter, GetFloatDigitsForSciNotnCorrectly) {
    EXPECT_EQ(digits::sciNotn::get(1.0L, 1), "1.0e+00");
    EXPECT_EQ(digits::sciNotn::get(1.0L, 2), "1.00e+00");
    EXPECT_EQ(digits::sciNotn::get(10.0L, 1), "1.0e+01");
    EXPECT_EQ(digits::sciNotn::get(0.1L, 1), "1.0e-01");
    EXPECT_EQ(digits::sciNotn::get(-0.1L, 1), "-1.0e-01");
    EXPECT_EQ(digits::sciNotn::get(15.0L, 1), "1.5e+01");
    EXPECT_EQ(digits::sciNotn::get(15.2L, 1), "1.5e+01");
}