#include "stl.h"
#include "aoc.h"

namespace day09 {

int64_t solve(std::istream& is, Task task, int n) {
    auto input = aoc::to_vector(boost::istream_range<int>(is));
    
    auto first_invalid = *boost::find_if(boost::adaptors::slice(input, n, input.size()), [n](const int& goal) {
        auto rng = boost::make_iterator_range(&goal - n, &goal);
        auto it = boost::find_if(rng, [&rng, goal](int x) {
            return x != goal - x && boost::find(rng, goal - x) != rng.end();
        });
        return it == rng.end();
    });

    if (task == Task::FIRST)
        return first_invalid;

    std::vector<int> sums = {0};
    boost::partial_sum(input, std::back_inserter(sums));

    size_t idx = *boost::find_if(boost::irange<size_t>(input.size()*input.size()), [&](size_t idx) {
        int x = idx % input.size();
        int y = idx / input.size();
        return x < y && sums[y]-sums[x] == first_invalid;
    });

    const int* px = input.data() + idx % input.size();
    const int* py = input.data() + idx / input.size();

    return *std::min_element(px, py) + *std::max_element(px, py);
}

} // namespace day09
