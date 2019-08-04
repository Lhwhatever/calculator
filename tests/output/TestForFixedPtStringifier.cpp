#include "gtest/gtest.h"

#include "calculator/FixedPtStringifier.h"
#include "calculator/Settings.h"

class UnitTestForFixedPtStringifier : public ::testing::Test {
   protected:
    SettingsImpl defaultSettings;
};

TEST_F(UnitTestForFixedPtStringifier, WhenDefaultStringifiesIntegersCorrectly) {
    FixedPtStringifier stringify{defaultSettings};
    EXPECT_EQ(stringify(5LL), "5");
    EXPECT_EQ(stringify(10LL), "10");
    EXPECT_EQ(stringify(-5LL), "-5");
    EXPECT_EQ(stringify(1234LL), "1 234");
    EXPECT_EQ(stringify(12345679LL), "12 345 679");
    EXPECT_EQ(stringify(123456789LL), "123 456 789");
    EXPECT_EQ(stringify(-987654LL), "-987 654");
}

TEST_F(UnitTestForFixedPtStringifier, WhenCustomStringifiesIntegersCorrectly) {
    FixedPtStringifier stringify{
        SettingsBuilder{}.grpBefDecimal(4).sepBefDecimal(",").make()};
    EXPECT_EQ(stringify(88888L), "8,8888");
}

TEST_F(UnitTestForFixedPtStringifier, WhenDefaultStringifiesFloatsCorrectly) {
    FixedPtStringifier stringify{defaultSettings};
    EXPECT_EQ(stringify(1.0L), "1.0");
    EXPECT_EQ(stringify(1000.0L), "1 000.0");
    EXPECT_EQ(stringify(-123456.0L), "-123 456.0");
    EXPECT_EQ(stringify(1.25L), "1.25");
    EXPECT_EQ(stringify(1.001L), "1.001");
    EXPECT_EQ(stringify(1.000001L), "1.0");
    EXPECT_EQ(stringify(1.999999L), "2.0");
}

TEST_F(UnitTestForFixedPtStringifier,
       WithFormatOptionsStringifiesFloatsCorrectly) {
    FixedPtStringifier stringify{SettingsBuilder{}
                                     .grpBefDecimal(4)
                                     .sepBefDecimal("'")
                                     .grpAftDecimal(4)
                                     .sepAftDecimal("'")
                                     .decimalPt(",")
                                     .make()};
    EXPECT_EQ(stringify(88888.88888L), "8'8888,8888'8");
}

TEST_F(UnitTestForFixedPtStringifier, WithDPPrecisionStringifiesCorrectly) {
    FixedPtStringifier stringify{
        SettingsBuilder{}
            .floatFixedPtPrecisionMode(modes::FixedPtPrecision::DEC_PT)
            .floatFixedPtFixedPrecision(6)
            .make()};
    EXPECT_EQ(stringify(1.2L), "1.200 000");
}

TEST_F(UnitTestForFixedPtStringifier, WithSFPrecisionStringifiesCorrectly) {
    FixedPtStringifier stringify{
        SettingsBuilder{}
            .floatFixedPtPrecisionMode(modes::FixedPtPrecision::SIG_FIG)
            .make()};
    EXPECT_EQ(stringify(0.1L), "0.100 0");
    EXPECT_EQ(stringify(0.01L), "0.010 00");
    EXPECT_EQ(stringify(0.0001L), "0.000 100 0");
    EXPECT_EQ(stringify(0.10001L), "0.100 0");
    EXPECT_EQ(stringify(-0.1L), "-0.100 0");

    EXPECT_EQ(stringify(1.2L), "1.200");
    EXPECT_EQ(stringify(200.0L), "200.0");

    EXPECT_EQ(stringify(2048.0L), "2 048");
    EXPECT_EQ(stringify(42300.0L), "42 300");
}
