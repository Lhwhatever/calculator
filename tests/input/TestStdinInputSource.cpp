#include "gtest/gtest.h"

#include "calculator/StdinInputSource.h"

TEST(UnitTest_StdinInput, OnReadItPromptsUserAndGetsResultRead) {
    std::stringstream inStream, outStream, errStream;
    StdinInputSource input{inStream, outStream, errStream};
    inStream << "0\n";
    auto received{input.read()};
    EXPECT_EQ(errStream.str(), "> ");
    EXPECT_EQ(received, "0");
}
