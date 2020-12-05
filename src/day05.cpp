#include "stl.h"
#include "aoc.h"

namespace day05 {

int64_t solve(std::istream& is, Task task) {
    auto input = boost::istream_range<std::string>(is);

    std::vector<int> seats;
    boost::transform(input, std::back_inserter(seats), [](const std::string& s) {
        return boost::accumulate(s, 0, [](int acc, char ch) {
            return 2 * acc + (ch == 'B' || ch == 'R');
        });
    });

    if (task == Task::FIRST) {
        return *boost::max_element(seats);
    } else {
        boost::sort(seats);
        return *boost::adjacent_find(seats, [](int a, int b) { return b != a + 1; })+1;
    }
}

} // namespace day05
