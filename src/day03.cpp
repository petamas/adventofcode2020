#include "stl.h"
#include "aoc.h"

namespace day03 {

int64_t solve(std::istream& is, Task task) {
    std::vector<std::string> input;
    boost::copy(boost::istream_range<std::string>(is), std::back_inserter(input));

    auto ans = [&input](int right, int down) -> int64_t {
        auto tree = [right](const auto& line) {
            return line.value()[right * line.index() % line.value().size()] == '#';
        };

        return boost::count_if(
            input | boost::adaptors::strided(down) | boost::adaptors::indexed(),
            tree);
    };

    if (task == Task::FIRST) {
        return ans(3, 1);
    } else {
        return ans(1, 1) * ans(3, 1) * ans(5, 1) * ans(7, 1) * ans(1, 2);
    }
}

} // namespace day03
