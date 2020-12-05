#include "stl.h"
#include "aoc.h"

namespace day04 {

class line_iterator
    : public boost::iterator_facade<line_iterator, const std::string, std::input_iterator_tag> {
public:
    line_iterator() = default;
    explicit line_iterator(std::istream& is, bool with_newline = false)
        : is(&is)
        , with_newline(with_newline)
    {
        increment();
    }
private:
    friend class boost::iterator_core_access;

    void increment() {
        std::getline(*is, line);
        if (with_newline)
            line += '\n';
    }

    bool equal(line_iterator const& other) const
    {
        return this->is == other.is || (this->end_of_stream() && other.end_of_stream());
    }

    const std::string& dereference() const {
        return line;
    }

    bool end_of_stream() const {
        return is == nullptr || is->fail();
    }

    std::istream* is = nullptr;
    bool with_newline = false;
    std::string line;
};

boost::iterator_range<line_iterator> line_range(std::istream& is, bool with_newline = false) {
    return { line_iterator(is, with_newline), line_iterator() };
}

namespace adl {
    template<class Range>
    auto begin(Range&& r) {
        using std::begin;
        return begin(std::forward<Range>(r));
    }

    template<class Range>
    auto end(Range&& r) {
        using std::end;
        return end(std::forward<Range>(r));
    }

}

template<class Func>
struct tokenizer_func {
    tokenizer_func(Func f) : f(std::move(f)) {}

    template <typename InputIterator, typename Token>
    bool operator()(InputIterator& next, InputIterator end, Token& tok) {
        if (next == end)
            return false;
        std::optional<Token> opt_tok = f(next, end);
        if (!opt_tok)
            return false;
        tok = *opt_tok;
        return true;
    }

    void reset() {}
private:
    Func f;
};

template <typename Token, typename InputIterator, typename Func>
auto make_tokenizer(InputIterator begin, InputIterator end, Func f)
    -> boost::tokenizer<tokenizer_func<Func>, InputIterator, Token>
{
    return { begin, end, tokenizer_func<Func>(std::move(f)) };
}

template <typename Token, typename Range, typename Func>
auto make_tokenizer(const Range& r, Func f)
    -> boost::tokenizer<tokenizer_func<Func>, decltype(adl::begin(r)), Token>
{
    return make_tokenizer<Token>(adl::begin(r), adl::end(r), std::move(f));
}

struct Passport {
    std::map<std::string, std::string> data;

    static Passport parse(const std::string& line) {
        std::stringstream ss(line);
        Passport passport;
        boost::transform(
            boost::istream_range<std::string>(ss),
            std::inserter(passport.data, passport.data.end()),
            [](const std::string& s) {
                auto pos = s.find(':');
                const std::string key(s.data(), pos);
                const std::string value(s.data() + pos + 1);
                return std::make_pair(key, value);
            }
        );
        return passport;
    }

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
            return it == fields.end() || it->second == nullptr || std::invoke(it->second, p.second);
        });

        return all_valid;
    }
};

int64_t solve(std::istream& is, Task task) {
    std::vector<std::string> input;
    boost::copy(line_range(is, true), std::back_inserter(input));

    auto lines = make_tokenizer<std::string>(input, [](auto& next, auto end) {
        auto begin = std::exchange(next, std::find(next, end, "\n"));
        std::string tok = std::accumulate(begin, next, std::string(""));
        if (next != end)
            ++next;
        return tok;
    });
        
    auto passports = boost::adaptors::transform(lines, &Passport::parse);
    return boost::count_if(passports, [&](const Passport& passport) {
        return passport.check(task == Task::SECOND);
    });
}

} // namespace day04
