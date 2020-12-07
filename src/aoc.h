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

/* split range */

template<class ForwardIterator>
using iterator_split_result = boost::iterator_range<boost::algorithm::split_iterator<ForwardIterator>>;

template<class Range>
using range_split_result = iterator_split_result<typename Range::const_iterator>;

template<class Range>
using range_split_element = boost::iterator_range<typename Range::const_iterator>;

template <typename ForwardIterator>
iterator_split_result<ForwardIterator> split(
    ForwardIterator first, ForwardIterator last,
    typename std::iterator_traits<ForwardIterator>::value_type separator)
{
    return iterator_split_result<ForwardIterator>(
        boost::algorithm::split_iterator<ForwardIterator>(first, last,
            boost::algorithm::token_finder([separator](const auto& value) { return value == separator; })),
        boost::algorithm::split_iterator<ForwardIterator>()
    );
}

template <typename Range>
range_split_result<Range> split(
    const Range& range,
    range_value_t<Range> separator)
{
    return split(adl::begin(range), adl::end(range), std::move(separator));
}

/* set operations */
template<class T>
std::set<T> set_intersection(const std::set<T>& a, const std::set<T>& b) {
    std::set<T> rv;
    boost::set_intersection(a, b, std::inserter(rv, rv.end()));
    return rv;
}

template<class T>
std::set<T> set_union(const std::set<T>& a, const std::set<T>& b) {
    std::set<T> rv;
    boost::set_union(a, b, std::inserter(rv, rv.end()));
    return rv;
}


} // namespace aoc

// Generated code, do not touch down from here
namespace day01 { int64_t solve(std::istream& is, Task task); }
namespace day02 { int64_t solve(std::istream& is, Task task); }
namespace day03 { int64_t solve(std::istream& is, Task task); }
namespace day04 { int64_t solve(std::istream& is, Task task); }
namespace day05 { int64_t solve(std::istream& is, Task task); }
namespace day06 { int64_t solve(std::istream& is, Task task); }
namespace day07 { int64_t solve(std::istream& is, Task task); }
