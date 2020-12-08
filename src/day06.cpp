#include "stl.h"
#include "aoc.h"

namespace day06 {

uint32_t compact_set(const std::string& s) {
    return boost::accumulate(boost::adaptors::transform(s, [](char c) { return 1 << (c - 'a'); }), 0, std::bit_or());
}

int64_t solve(std::istream& is, Task task) {
    using input_t = std::vector<std::string>;
    input_t input = aoc::to_vector(aoc::line_range(is));

    auto summarize_group = [task](const aoc::range_split_element<input_t>& group) {
        auto compact_group = boost::adaptors::transform(group, compact_set);
        uint32_t init = group.empty() ? 0 : *compact_group.begin();
        uint32_t group_result = task == Task::FIRST
            ? boost::accumulate(compact_group, init, std::bit_or())
            : boost::accumulate(compact_group, init, std::bit_and());
        return std::bitset<32>(group_result).count(); // no popcount() yet
    };

    auto groups = boost::adaptors::transform(aoc::split(input, ""), summarize_group);

    return boost::accumulate(groups, 0);
}

} // namespace day06
