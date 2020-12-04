#include "stl.h"
#include "aoc.h"

namespace day04 {

using PassportData = std::map<std::string, std::string>;

struct Passport {
    PassportData data;
};

std::istream& operator>>(std::istream& is, Passport& passport) {
    std::string line;
    std::getline(is, line);
    std::stringstream ss(line);
    passport.data.clear();
    boost::transform(
        boost::istream_range<std::string>(ss),
        std::inserter(passport.data, passport.data.end()),
        [](const std::string& s) {
            auto pos = s.find(':');
            const std::string key(s.data(), pos);
            const std::string value(s.data() + pos + 1);
            return PassportData::value_type(key, value);
        });
    return is;
}

std::ostream& operator<<(std::ostream& os, const Passport& passport) {
    boost::transform(passport.data, std::ostream_iterator<std::string>(os, " "), [](const PassportData::value_type& p){
        return p.first + ": \"" + p.second + "\"";
    });
    return os;
}

int64_t solve(std::istream& is, Task task) {
    std::vector<Passport> input;
    boost::copy(boost::istream_range<Passport>(is), std::back_inserter(input));
    input = boost::accumulate(input, std::vector<Passport>(1), [](std::vector<Passport> acc, const Passport& current) {
        if (current.data.empty()) {
            // start new logical line
            acc.emplace_back();
        } else {
            // expand on previous line
            acc.back().data.insert(current.data.begin(), current.data.end());
        }
        return acc;
    });

    // boost::copy(input, std::ostream_iterator<Passport>(std::cout, "\n"));

    return boost::count_if(input, [](const Passport& passport) {
        auto has_field = [&passport](const std::string& s) { return passport.data.find(s) != passport.data.end(); };
        return has_field("byr")
            && has_field("iyr")
            && has_field("eyr")
            && has_field("hgt")
            && has_field("hcl")
            && has_field("ecl")
            && has_field("pid");
    });
}

} // namespace day04
