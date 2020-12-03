#include "stl.h"
#include "aoc.h"
#include "input02.h"
#include "gtest/gtest.h"

TEST(day02first, example)
{
    std::stringstream ss(day02::example_input);
    EXPECT_EQ(day02::solve(ss, Task::FIRST), 2);
}

TEST(day02first, personal)
{
    std::stringstream ss(day02::personal_input);
    EXPECT_EQ(day02::solve(ss, Task::FIRST), 500);
}

TEST(day02second, example)
{
    std::stringstream ss(day02::example_input);
    EXPECT_EQ(day02::solve(ss, Task::SECOND), 1);
}

TEST(day02second, personal)
{
    std::stringstream ss(day02::personal_input);
    EXPECT_EQ(day02::solve(ss, Task::SECOND), 313);
}
