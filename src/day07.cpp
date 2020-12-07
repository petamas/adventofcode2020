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


struct Req {
    size_t color;
    size_t num;
};

struct Bag {
    size_t color;
    std::vector<Req> reqs;

    static Bag parse(const std::string& line) {
        const std::regex line_regex(R"((\w+ \w+) bags contain.*)");
        std::smatch line_match;
        bool line_success = std::regex_match(line, line_match, line_regex) && line_match.size() == 2;
        assert(line_success);

        Bag bag;
        bag.color = color_id(line_match[1].str());

        const std::regex req_regex(R"((\d+) (\w+ \w+) bags?)");

        std::transform(
            std::sregex_iterator(line.begin(), line.end(), req_regex),
            std::sregex_iterator(),
            std::back_inserter(bag.reqs),
            [](const std::smatch& match) {
                return Req{ color_id(match[2].str()), boost::lexical_cast<size_t>(match[1].str()) };
            }
        );
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
