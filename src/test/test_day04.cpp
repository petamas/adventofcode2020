#include "stl.h"
#include "aoc.h"
#include "input04.h"
#include "gtest/gtest.h"

TEST(day04first, example)
{
    std::stringstream ss(day04::example_input);
    EXPECT_EQ(day04::solve(ss, Task::FIRST), 2);
}

TEST(day04first, personal)
{
    std::stringstream ss(day04::personal_input);
    EXPECT_EQ(day04::solve(ss, Task::FIRST), 256);
}

TEST(day04second, example)
{
    std::stringstream ss(day04::example_input);
    EXPECT_EQ(day04::solve(ss, Task::SECOND), 2);
}

TEST(day04second, personal)
{
    std::stringstream ss(day04::personal_input);
    EXPECT_EQ(day04::solve(ss, Task::SECOND), 198);
}
