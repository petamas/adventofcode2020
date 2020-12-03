#include "stl.h"
#include "aoc.h"
#include "input01.h"
#include "gtest/gtest.h"

TEST(day01first, example)
{
    std::stringstream ss(day01::example_input);
    EXPECT_EQ(day01::solve(ss, Task::FIRST), 514579);
}

TEST(day01first, personal)
{
    std::stringstream ss(day01::personal_input);

    EXPECT_EQ(day01::solve(ss, Task::FIRST), 956091);
}

TEST(day01second, example)
{
    std::stringstream ss(day01::example_input);
    EXPECT_EQ(day01::solve(ss, Task::SECOND), 241861950);
}

TEST(day01second, personal)
{
    std::stringstream ss(day01::personal_input);
    EXPECT_EQ(day01::solve(ss, Task::SECOND), 79734368);
}
