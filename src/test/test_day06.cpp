#include "stl.h"
#include "aoc.h"
#include "input06.h"
#include "gtest/gtest.h"

TEST(day06first, example)
{
    std::stringstream ss(day06::example_input);
    EXPECT_EQ(day06::solve(ss, Task::FIRST), 11);
}

TEST(day06first, personal)
{
    std::stringstream ss(day06::personal_input);
    EXPECT_EQ(day06::solve(ss, Task::FIRST), 6532);
}

TEST(day06second, example)
{
    std::stringstream ss(day06::example_input);
    EXPECT_EQ(day06::solve(ss, Task::SECOND), 6);
}

TEST(day06second, personal)
{
    std::stringstream ss(day06::personal_input);
    EXPECT_EQ(day06::solve(ss, Task::SECOND), 3427);
}
