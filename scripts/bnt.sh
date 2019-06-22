#!/bin/bash
COLOR_RED="\e[1;31m"
COLOR_MAGENTA="\e[35m"
COLOR_GREEN="\e[1;32m"
COLOR_RESET="\e[0m"

COLOR_ERROR=$COLOR_RED
COLOR_WARN=$COLOR_MAGENTA
COLOR_SUCCESS=$COLOR_GREEN

COMPILE_TMP=".compile-msg"
TEST_TMP=".test-msg"
TEST_BIN="bin/test/tester"

echo -e "Begin building. Compiling test..."
START=`date '+%s'`

make testbin > $COMPILE_TMP 2> /dev/null
COMPILE_RESULT=$?

END=`date '+%s'`
echo "Checking for compilation errors and warnings..."

if grep 'error: ' $COMPILE_TMP > /dev/null ; then
    echo -e "$(cat $COMPILE_TMP)"
    echo -e $COLOR_ERROR"Error in compiling."$COLOR_RESET
    rm $COMPILE_TMP
    exit 1
elif grep 'warning: ' $COMPILE_TMP > /dev/null ; then
    echo -e "$(cat $COMPILE_TMP)"
    echo -e $COLOR_WARN"Warnings while compiling."$COLOR_RESET
    rm $COMPILE_TMP
    exit 2
elif grep 'error: ld ' $COMPILE_TMP > /dev/null ; then
    echo -e "$(cat $COMPILE_TMP)"
    echo -e $COLOR_ERROR"Error in linking."$COLOR_RESET
    rm $COMPILE_TMP
    exit 3
elif [[ $COMPILE_RESULT = 0 ]] ; then
    echo -e $COLOR_SUCCESS"Compiled successfully."$COLOR_RESET
    echo -e "Compiled in $(date '+%T' -u -d @$(expr $END - $START))"
    rm $COMPILE_TMP
else
    echo -e "$(cat $COMPILE_TMP)"
    echo -e $COLOR_ERROR"Unknown error."$COLOR_RESET
    rm $COMPILE_TMP
    exit -1
fi

if [ -t 1 ] ; then
    TEST_FLAGS="--gtest_color=yes"
else
    TEST_FLAGS=""
fi

$TEST_BIN $TEST_FLAGS $@ > $TEST_TMP
if [[ $? = 0 ]] ; then
    echo -e $COLOR_SUCCESS"All tests passed."$COLOR_RESET
    rm $TEST_TMP
    exit 0
else
    echo -e "$(cat $TEST_TMP)"
    rm $TEST_TMP
    exit 4
fi