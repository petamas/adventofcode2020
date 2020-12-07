#include "stl.h"
#include "aoc.h"

namespace day06 {

int64_t solve(std::istream& is, Task task) {
    using input_t = std::vector<std::string>;
    input_t input = aoc::to_vector(aoc::line_range(is));

    auto summarize_group = [task](const aoc::range_split_element<input_t>& group) {
        std::set<char> init = group.empty() ? std::set<char>{} : aoc::to_set(*group.begin());
        std::set<char> group_result = boost::accumulate(
            boost::adaptors::transform(group, aoc::to_set<std::string>),
            init,
            task == Task::FIRST ? aoc::set_union<char> : aoc::set_intersection<char>);
        return group_result.size();
    };

    auto groups = boost::adaptors::transform(aoc::split(input, ""), summarize_group);

    return boost::accumulate(groups, 0);
}

} // namespace day06
