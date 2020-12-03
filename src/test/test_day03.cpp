#include "stl.h"
#include "aoc.h"
#include "input03.h"
#include "gtest/gtest.h"

TEST(day03first, example)
{
    std::stringstream ss(day03::example_input);
    EXPECT_EQ(day03::solve(ss, Task::FIRST), 7);
}

TEST(day03first, personal)
{
    std::stringstream ss(day03::personal_input);
    EXPECT_EQ(day03::solve(ss, Task::FIRST), 289);
}

TEST(day03second, example)
{
    std::stringstream ss(day03::example_input);
    EXPECT_EQ(day03::solve(ss, Task::SECOND), 336);
}

TEST(day03second, personal)
{
    std::stringstream ss(day03::personal_input);
    EXPECT_EQ(day03::solve(ss, Task::SECOND), 5522401584);
}
