#include "stl.h"
#include "aoc.h"

namespace day05 {

struct pos {
    std::pair<int, int> row;
    std::pair<int, int> col;

    int id() const {
        assert(row.second == row.first + 1);
        assert(col.second == col.first + 1);
        return row.first * 8 + col.first;
    }
};

int64_t solve(std::istream& is, Task task) {
    std::vector<std::string> input;
    boost::copy(boost::istream_range<std::string>(is), std::back_inserter(input));

    std::vector<int> seats;
    boost::transform(input, std::back_inserter(seats), [](const std::string& s) {
        return boost::accumulate(s, pos{ {0,128}, {0,8} },
            [](const pos& p, char ch) -> pos {
                switch (ch) {
                case 'F': return { {p.row.first, (p.row.first + p.row.second) / 2}, p.col };
                case 'B': return { {(p.row.first + p.row.second) / 2, p.row.second}, p.col };
                case 'L': return { p.row, {p.col.first, (p.col.first + p.col.second) / 2} };
                case 'R': return { p.row, {(p.col.first + p.col.second) / 2, p.col.second} };
                default: return p;
                }
            }
        ).id();
    });

    if (task == Task::FIRST) {
        return *boost::max_element(seats);
    } else {
        boost::sort(seats);
        return *boost::adjacent_find(seats, [](int a, int b) { return b != a + 1; })+1;
    }
}

} // namespace day05
