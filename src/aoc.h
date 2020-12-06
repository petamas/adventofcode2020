#pragma once

#include "stl.h"

enum class Task { FIRST, SECOND };

namespace adl {
template<class Range>
typename boost::range_iterator<Range>::type begin(Range&& r) {
    using std::begin;
    return begin(std::forward<Range>(r));
}

template<class Range>
typename boost::range_iterator<Range>::type end(Range&& r) {
    using std::end;
    return end(std::forward<Range>(r));
}
} // namespace adl

namespace aoc {

/* std::remove_cvref (C++20) */

template< class T >
struct remove_cvref {
    typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};

template< class T >
using remove_cvref_t = typename remove_cvref<T>::type;

/* range_XXX_t */

template<class Range>
using range_iterator_t = typename boost::range_iterator<Range>::type;

template<class Range>
using range_value_t = typename boost::range_value<Range>::type;

/* to_vector(Range) */

template<class Range>
std::vector<range_value_t<Range>> to_vector(const Range& r) {
    return std::vector<range_value_t<Range>>(adl::begin(r), adl::end(r));
}

template<class Range>
std::set<range_value_t<Range>> to_set(const Range& r) {
    return std::set<range_value_t<Range>>(adl::begin(r), adl::end(r));
}


/* istream skip() */

template<class T>
struct skip_t { T wrapped; };

template<class T>
skip_t<T> skip(T to_skip) { return skip_t<T>{to_skip}; }

template<class T>
std::istream& operator>>(std::istream& is, const skip_t<T>& skipper) {
    boost::io::ios_flags_saver ifs(is);
    T tmp;
    is >> std::noskipws >> tmp;

    if (tmp != skipper.wrapped) {
        is.setstate(std::ios_base::failbit);
    }
    return is;
}

/* istream line_iterator */

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

inline boost::iterator_range<line_iterator> line_range(std::istream& is, bool with_newline = false) {
    return { line_iterator(is, with_newline), line_iterator() };
}

/* boost::tokenizer wrapper */

template<class Func>
struct simple_tokenizer_func {
    simple_tokenizer_func(Func f)
        : f(std::move(f))
    {}

    template <typename InputIterator, typename Token>
    bool operator()(InputIterator& next, InputIterator end, Token& tok) {
        if (next == end)
            return false;
        return f(next, end, tok);
    }

    void reset() {}
private:
    Func f;
};

template <typename Token, typename InputIterator, typename Func>
boost::tokenizer<Func, InputIterator, Token>
make_tokenizer(InputIterator begin, InputIterator end, Func f)
{
    return boost::tokenizer<Func, InputIterator, Token>(begin, end, std::move(f));
}

template <typename Token, typename Range, typename Func>
boost::tokenizer<Func, range_iterator_t<const Range>, Token>
make_tokenizer(const Range& r, Func f)
{
    return make_tokenizer<Token>(adl::begin(r), adl::end(r), std::move(f));
}

template <typename Token, typename InputIterator, typename Func>
boost::tokenizer<simple_tokenizer_func<Func>, InputIterator, Token>
make_simple_tokenizer(InputIterator begin, InputIterator end, Func f)
{
    return make_tokenizer<Token>(begin, end, simple_tokenizer_func<Func>(std::move(f)));
}

template <typename Token, typename Range, typename Func>
boost::tokenizer<simple_tokenizer_func<Func>, typename boost::range_iterator<const Range>::type, Token>
make_simple_tokenizer(const Range& r, Func f)
{
    return make_simple_tokenizer<Token>(adl::begin(r), adl::end(r), std::move(f));
}

template<typename ForwardIterator>
struct split_range_function {
    using value_type = typename std::iterator_traits<ForwardIterator>::value_type;

    split_range_function(value_type separator)
        : separator(std::move(separator))
    {}

    template <typename InputIterator>
    bool operator()(InputIterator& next, InputIterator end, boost::iterator_range<ForwardIterator>& tok) {
        if (done)
            return false;

        ForwardIterator begin = std::exchange(next, std::find(next, end, separator));
        tok = boost::iterator_range<ForwardIterator>(begin, next);
        if (next == end)
            done = true;
        else
            ++next;

        return true;
    }

    void reset() { done = false; }
private:
    value_type separator;
    bool done = false;
};

template<typename ForwardIterator>
using split_range_tokenizer = boost::tokenizer<split_range_function<ForwardIterator>, ForwardIterator, boost::iterator_range<ForwardIterator>>;

template <typename ForwardIterator>
split_range_tokenizer<ForwardIterator> split_range(
    ForwardIterator first, ForwardIterator last,
    typename std::iterator_traits<ForwardIterator>::value_type separator)
{
    return { first, last, split_range_function<ForwardIterator>(std::move(separator)) };
}

template <typename Range>
split_range_tokenizer<range_iterator_t<Range>> split_range(
    const Range& range,
    range_value_t<Range> separator)
{
    return split_range(adl::begin(range), adl::end(range), std::move(separator));
}

} // namespace aoc

// Generated code, do not touch down from here
namespace day01 { int64_t solve(std::istream& is, Task task); }
namespace day02 { int64_t solve(std::istream& is, Task task); }
namespace day03 { int64_t solve(std::istream& is, Task task); }
namespace day04 { int64_t solve(std::istream& is, Task task); }
namespace day05 { int64_t solve(std::istream& is, Task task); }
namespace day06 { int64_t solve(std::istream& is, Task task); }
