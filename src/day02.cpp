#include "stl.h"
#include "aoc.h"

namespace day02 {

struct Line {
    int minimum, maximum;
    char ch;
    std::string password;
};

std::istream& operator>>(std::istream& is, Line& line) {
    return is
        >> line.minimum >> aoc::skip('-') >> line.maximum
        >> aoc::skip(' ') >> line.ch
        >> aoc::skip(':') >> line.password;
}

int64_t solve(std::istream& is, Task task) {
    auto input = boost::istream_range<Line>(is);

    if (task == Task::FIRST) {
        return boost::count_if(input, [](const Line& line) {
            int c = boost::count(line.password, line.ch);
            return c >= line.minimum && c <= line.maximum;
        });
    } else {
        return boost::count_if(input, [](const Line& line) {
            return (line.password[line.minimum - 1] == line.ch)
                 + (line.password[line.maximum - 1] == line.ch) == 1;
        });
    }
}

} // namespace day02
