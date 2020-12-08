#include "stl.h"
#include "aoc.h"

namespace day07 {

size_t color_id(const std::string& s) {
    static std::map<std::string, size_t> db;
    if (db.find(s) == db.end()) {
        db.emplace(s, db.size());
    }
    return db[s];
}

size_t color_id(const std::string adj, const std::string col) {
    return color_id(adj + " " + col);
}

struct Req {
    size_t color;
    size_t num;
};

std::istream& operator>>(std::istream& is, Req& req) {
    std::array<std::string, 3> words;
    if (is >> req.num >> words[0] >> words[1] >> words[2])
        req.color = color_id(words[0], words[1]);
    return is;
}

struct Bag {
    size_t color;
    std::vector<Req> reqs;

    static Bag parse(const std::string& line) {
        std::stringstream ss(line);
        std::array<std::string, 4> words;
        ss >> words[0] >> words[1] >> words[2] >> words[3];

        Bag bag;
        bag.color = color_id(words[0], words[1]);
        boost::copy(boost::istream_range<Req>(ss), std::back_inserter(bag.reqs));
        return bag;
    }
};

using graph_t = std::vector<Bag>;

enum class has_path_t { unknown, yes, no };

using has_path_cache_t = std::map<std::pair<size_t, size_t>, has_path_t>;

has_path_t has_path(const graph_t& bags, size_t from, size_t to, has_path_cache_t& cache) {
    has_path_t& rv = cache[std::make_pair(from, to)];

    if (rv != has_path_t::unknown)
        return rv;

    if (from == to)
        return rv = has_path_t::yes;

    return rv = boost::algorithm::any_of(bags[from].reqs, [&](const Req& req) { return has_path(bags, req.color, to, cache)==has_path_t::yes; }) ? has_path_t::yes : has_path_t::no;
}

size_t subgraph_size(const graph_t& bags, size_t root) {
    return 1 + boost::accumulate(
        boost::adaptors::transform(bags[root].reqs, [&](const Req& req) {
            return req.num * subgraph_size(bags, req.color);
        }), 0u);
}

int64_t solve(std::istream& is, Task task) {
    graph_t bags = aoc::to_vector(boost::adaptors::transform(aoc::line_range(is), &Bag::parse));
    boost::sort(bags, [](const Bag& a, const Bag& b) { return a.color < b.color; });

    const size_t shiny_gold = color_id("shiny gold");

    if (task == Task::FIRST) {
        has_path_cache_t cache;
        auto goal_reachable = [&](const Bag& bag) {
            return has_path(bags, bag.color, shiny_gold, cache) == has_path_t::yes;
        };
        return boost::count_if(bags, goal_reachable) - 1;
    } else {
        return subgraph_size(bags, shiny_gold)-1;
    }
}

} // namespace day07
