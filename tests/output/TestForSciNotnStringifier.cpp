#include "gtest/gtest.h"

#include "calculator/SciNotnStringifier.h"
#include "calculator/Settings.h"

class UnitTestForSciNotnStringifier : public ::testing::Test {
   protected:
    SettingsImpl defaultSettings;
};

TEST_F(UnitTestForSciNotnStringifier, WhenDefaultStringifiesCorrectly) {
    SciNotnStringifier stringify{defaultSettings};

    EXPECT_EQ(stringify(100.0L), "1.0e+2");
    EXPECT_EQ(stringify(200.0L), "2.0e+2");
    EXPECT_EQ(stringify(1000.0L), "1.0e+3");
    EXPECT_EQ(stringify(-1000.0L), "-1.0e+3");
    EXPECT_EQ(stringify(10000LL), "1.0e+4");
    EXPECT_EQ(stringify(1.234567e-89L), "1.234 567e-89");
}

TEST_F(UnitTestForSciNotnStringifier, WhenCustomStringifiesCorrectly) {
    SciNotnStringifier stringify{SettingsBuilder{}
                                     .decimalPt(",")
                                     .grpAftDecimal(2)
                                     .sepAftDecimal("'")
                                     .omitPlusInExponent(true)
                                     .sciNotnExponent("*10^")
                                     .sciNotnPrecision(4)
                                     .make()};
    EXPECT_EQ(stringify(123.4L), "1,23'40*10^2");
}