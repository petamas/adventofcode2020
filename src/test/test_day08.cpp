#include "stl.h"
#include "aoc.h"
#include "input08.h"
#include "gtest/gtest.h"

TEST(day08first, example)
{
    std::stringstream ss(day08::example_input);
    EXPECT_EQ(day08::solve(ss, Task::FIRST), 5);
}

TEST(day08first, personal)
{
    std::stringstream ss(day08::personal_input);
    EXPECT_EQ(day08::solve(ss, Task::FIRST), 1137);
}

TEST(day08second, example)
{
    std::stringstream ss(day08::example_input);
    EXPECT_EQ(day08::solve(ss, Task::SECOND), 8);
}

TEST(day08second, personal)
{
    std::stringstream ss(day08::personal_input);
    EXPECT_EQ(day08::solve(ss, Task::SECOND), 1125);
}
