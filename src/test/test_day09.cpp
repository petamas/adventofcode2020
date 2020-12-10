#include "stl.h"
#include "aoc.h"
#include "input09.h"
#include "gtest/gtest.h"

TEST(day09first, example)
{
    std::stringstream ss(day09::example_input);
    EXPECT_EQ(day09::solve(ss, Task::FIRST, 5), 127);
}

TEST(day09first, personal)
{
    std::stringstream ss(day09::personal_input);
    EXPECT_EQ(day09::solve(ss, Task::FIRST, 25), 104054607);
}

TEST(day09second, example)
{
    std::stringstream ss(day09::example_input);
    EXPECT_EQ(day09::solve(ss, Task::SECOND, 5), 62);
}

TEST(day09second, personal)
{
    std::stringstream ss(day09::personal_input);
    EXPECT_EQ(day09::solve(ss, Task::SECOND, 25), 13935797);
}
