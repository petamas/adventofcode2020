#include "stl.h"
#include "aoc.h"
#include "input07.h"
#include "gtest/gtest.h"

TEST(day07first, example)
{
    std::stringstream ss(day07::example_input);
    EXPECT_EQ(day07::solve(ss, Task::FIRST), 4);
}

TEST(day07first, personal)
{
    std::stringstream ss(day07::personal_input);
    EXPECT_EQ(day07::solve(ss, Task::FIRST), 229);
}

TEST(day07second, example)
{
    std::stringstream ss(day07::example_input);
    EXPECT_EQ(day07::solve(ss, Task::SECOND), 32);
}

TEST(day07second, personal)
{
    std::stringstream ss(day07::personal_input);
    EXPECT_EQ(day07::solve(ss, Task::SECOND), 6683);
}
