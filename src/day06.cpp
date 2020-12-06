#include "stl.h"
#include "aoc.h"

namespace day06 {

int64_t solve(std::istream& is, Task task) {
    std::vector<std::string> input = aoc::to_vector(aoc::line_range(is,true));

    auto lines = aoc::make_tokenizer<std::set<char>>(input, [task](auto& next, auto end) {
        auto begin = std::exchange(next, std::find(next, end, "\n"));
        std::set<char> init;
        if (task == Task::SECOND) {
            boost::copy(boost::irange<char>('a', 'z'+1), std::inserter(init, init.end()));
            init.insert('\n');
        }
        std::set<char> tok = std::accumulate(begin, next, init,
            [task](const std::set<char>& acc, const std::string& line) {
                std::set<char> rv;
                std::set<char> current(line.begin(), line.end());
                if (task == Task::FIRST) {
                    boost::set_union(acc, current, std::inserter(rv, rv.end()));
                } else {
                    boost::set_intersection(acc, current, std::inserter(rv, rv.end()));
                }
                return rv;
            });
        if (next != end)
            ++next;
        return tok;
    });

    return boost::accumulate(lines, 0, [](int acc, const std::set<char>& line) {
        return acc + line.size()-1;
    });
}

} // namespace day06
