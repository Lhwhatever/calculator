#include "gtest/gtest.h"

#include "calculator/SciNotnStringifier.h"
#include "calculator/Settings.h"

class UnitTestForSciNotnStringifier : public ::testing::Test {
   protected:
    SettingsImpl defaultSettings;
};

TEST_F(UnitTestForSciNotnStringifier, WhenDefaultStringifiesIntegersCorrectly) {
    SciNotnStringifier stringify{defaultSettings};

    EXPECT_EQ(stringify(100.0L), "1.0e+2");
    EXPECT_EQ(stringify(200.0L), "2.0e+2");
    EXPECT_EQ(stringify(1000.0L), "1.0e+3");
    EXPECT_EQ(stringify(-1000.0L), "-1.0e+3");
    EXPECT_EQ(stringify(10000LL), "1.0e+4");
    EXPECT_EQ(stringify(1.234567e-89L), "1.234 567e-89");
}
