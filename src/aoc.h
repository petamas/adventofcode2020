#pragma once

#include "stl.h"

enum class Task { FIRST, SECOND };

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

// Generated code, do not touch down from here
namespace day01 { int64_t solve(std::istream& is, Task task); }
namespace day02 { int64_t solve(std::istream& is, Task task); }
namespace day03 { int64_t solve(std::istream& is, Task task); }
namespace day04 { int64_t solve(std::istream& is, Task task); }
