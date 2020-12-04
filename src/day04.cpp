#include "stl.h"
#include "aoc.h"

namespace day04 {

using PassportData = std::map<std::string, std::string>;

struct Passport {
    PassportData data;
    using value_type = PassportData::value_type;

    static bool validate_yr(const std::string& s, int min, int max) {
        if (s.size() != 4 || !boost::algorithm::all_of(s, isdigit))
            return false;
        int yr = boost::lexical_cast<int>(s.data());
        return min <= yr && yr <= max;
    }

    static bool validate_byr(const std::string& s) { return validate_yr(s, 1920, 2002); }
    static bool validate_iyr(const std::string& s) { return validate_yr(s, 2010, 2020); }
    static bool validate_eyr(const std::string& s) { return validate_yr(s, 2020, 2030); }
    static bool validate_hgt(const std::string& s) {
        if (s.size() < 3)
            return false;

        size_t len = s.size() - 2;
        std::string_view num(s.data(), len);
        std::string_view unit(s.data() + len, 2);
        if (!boost::algorithm::all_of(num, isdigit))
            return false;

        int hgt = boost::lexical_cast<int>(s.data(), len);
        if (unit == "cm") {
            return 150 <= hgt && hgt <= 193;
        } else if (unit == "in") {
            return 59 <= hgt && hgt <= 76;
        } else {
            return false;
        }
    }

    static bool validate_hcl(const std::string& s) {
        return s.size() == 7 && s[0] == '#' && std::all_of(s.begin() + 1, s.end(), isxdigit);
    }

    static bool validate_ecl(const std::string& s) {
        static std::set<std::string> colors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        return colors.find(s) != colors.end();
    }

    static bool validate_pid(const std::string& s) {
        return s.size()==9 && boost::algorithm::all_of(s, isdigit);
    }

    bool check(bool validate) const {
        static const std::map<std::string, bool(*)(const std::string&)> fields = {
            {"byr", validate_byr},
            {"iyr", validate_iyr},
            {"eyr", validate_eyr},
            {"hgt", validate_hgt},
            {"hcl", validate_hcl},
            {"ecl", validate_ecl},
            {"pid", validate_pid}
        };
        bool all_present = boost::algorithm::all_of(fields, [this](const auto& p) {
            return data.find(p.first) != data.end();
        });
        if (!all_present)
            return false;

        if (!validate)
            return true;

        bool all_valid = boost::algorithm::all_of(data, [](const auto& p) {
            auto it = fields.find(p.first);
            return it == fields.end() || it->second == nullptr || (*it->second)(p.second);
        });

        return all_valid;
    }
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

    return boost::count_if(input, [&](const Passport& passport) {
        return passport.check(task == Task::SECOND);
    });
}

} // namespace day04
