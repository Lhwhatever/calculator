#include "gtest/gtest.h"

#include "calculator/StdinInputSource.h"

TEST(UnitTestStdinInput, OnReadItPromptsUserAndGetsResultRead) {
    std::stringstream inStream, outStream, errStream;
    StdinInputSource input{inStream, outStream, errStream};
    inStream << "0\n";
    EXPECT_EQ(input.read(), "0");
    EXPECT_EQ(errStream.str(), "> ");
}

TEST(UnitTestStdinInput, OnReadItClearsPreviousLine) {
    std::stringstream inStream, outStream, errStream;
    StdinInputSource input{inStream, outStream, errStream};
    inStream << "abc\n";
    EXPECT_EQ(input.read(), "abc");
    EXPECT_EQ(errStream.str(), "> ");
    errStream.str("");
    errStream.clear();

    inStream << "def\n";
    EXPECT_EQ(input.read(), "def");
    EXPECT_EQ(errStream.str(), "> ");
}

TEST(UnitTestStdinInput, CanProperlyReadMultilineInput) {
    std::stringstream inStream, outStream, errStream;
    StdinInputSource input{inStream, outStream, errStream};

    inStream << "2\\\n+2";
    ASSERT_EQ(input.read(), "2+2");
    ASSERT_EQ(errStream.str(), "> ... ");
    errStream.str("");
    errStream.clear();

    inStream << "1\\\n+2\\\n+3";
    ASSERT_EQ(input.read(), "1+2+3");
    ASSERT_EQ(errStream.str(), "> ... ... ");
}

TEST(UnitTestStdinInput, CanReadEmptyStrings) {
    std::stringstream inStream, outStream, errStream;
    StdinInputSource input{inStream, outStream, errStream};

    ASSERT_EQ(input.read(), "");

    inStream << "";
    ASSERT_EQ(input.read(), "");
}
