#include <CppUTest/CommandLineTestRunner.h>

/** @defgroup tests Tests
 * @brief All tests for this project.
 */

/** @defgroup unit_tests Unit Tests
 * @ingroup tests
 * @brief All unit tests for this project.
 *
 */

/** @ingroup unit_tests
 * @brief Entry point when running tests.
 *
 * As this project makes use of <a
 * href="http://cpputest.github.io/">CppUTest</a>, this `main` function merely
 * acts as a wrapper around `static int CommandLineTestRunner::RunAllTests(int
 * argc, char** argv)`;
 */

int main(int argc, char** argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}