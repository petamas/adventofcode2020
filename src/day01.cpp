#include "stl.h"
#include "aoc.h"

namespace day01 {

int64_t solve(std::istream& is, Task task) {
    std::vector<int> input = aoc::to_vector(boost::istream_range<int>(is));
    boost::sort(input);
    auto pred = [&](int x) { return boost::binary_search(input, 2020 - x); };
    auto ans = [](auto... xs) { return ((2020 - (xs + ...)) * ... * xs); };

    if (task == Task::FIRST) {
        int x = *boost::find_if(input, pred);
        return ans(x);
    }
    else {
        const size_t n = input.size();
        size_t idx = *boost::find_if(boost::irange<size_t>(n*n), [&](size_t idx) {
            return pred(input[idx%n] + input[idx/n]);
        });
        return ans(input[idx/n], input[idx%n]);
    }
}

} // namespace day01