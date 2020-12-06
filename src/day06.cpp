#include "stl.h"
#include "aoc.h"

namespace day06 {

int64_t solve(std::istream& is, Task task) {
    std::vector<std::string> input = aoc::to_vector(aoc::line_range(is));
    auto groups = aoc::split_range(input.begin(), input.end(), "");

    std::set<char> init;
    if (task == Task::SECOND) {
        init = aoc::to_set(boost::irange<char>('a', 'z' + 1));
    }

    return boost::accumulate(boost::adaptors::transform(groups, [&init, task](const auto& group) {
        return boost::accumulate(group, init, [task](const std::set<char>& acc, const std::string& person){
            std::set<char> rv;
            std::set<char> current = aoc::to_set(person);
            if (task == Task::FIRST)
                boost::set_union(acc, current, std::inserter(rv, rv.end()));
            else
                boost::set_intersection(acc, current, std::inserter(rv, rv.end()));
            return rv;
        }).size();
    }), 0);
}

} // namespace day06
