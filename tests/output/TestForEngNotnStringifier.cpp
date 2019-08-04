#include "gtest/gtest.h"

#include "calculator/EngNotnStringifier.h"
#include "calculator/Settings.h"

class UnitTestForEngNotnStringifier : public ::testing::Test {
   protected:
    SettingsImpl defaultSettings;
};

TEST_F(UnitTestForEngNotnStringifier, WhenDefaultStringifiesCorrectly) {
    EngNotnStringifier stringify{defaultSettings};

    /*
        EXPECT_EQ(stringify(1.0L), "1.0e+0");
        EXPECT_EQ(stringify(1000.0L), "1.0e+3");
        EXPECT_EQ(stringify(1000000.0L), "1.0e+6");
        EXPECT_EQ(stringify(0.001), "1.0e-3");
        */
}