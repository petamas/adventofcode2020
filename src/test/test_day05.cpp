#include "stl.h"
#include "aoc.h"
#include "input05.h"
#include "gtest/gtest.h"

TEST(day05first, example)
{
    std::stringstream ss(day05::example_input);
    EXPECT_EQ(day05::solve(ss, Task::FIRST), 820);
}

TEST(day05first, personal)
{
    std::stringstream ss(day05::personal_input);
    EXPECT_EQ(day05::solve(ss, Task::FIRST), 908);
}

TEST(day05second, personal)
{
    std::stringstream ss(day05::personal_input);
    EXPECT_EQ(day05::solve(ss, Task::SECOND), 619);
}
