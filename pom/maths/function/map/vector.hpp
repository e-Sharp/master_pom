#pragma once

#include "pom/maths/vector/vector.hpp"

namespace pom {

template<typename Tr, typename F> constexpr
auto mapped_d(const vector<Tr>& v, F f) {
    auto m = vector<Tr>{};
    for(std::size_t i = 0; i < Tr::size; ++i) {
        at(m, i) = f(at(v, i));
    }
    return m;
}

// F: (v, i) -> e.
template<typename Traits, typename F> constexpr
auto mapped_i(const vector<Traits>& v, F f) {
    auto m = vector<Traits>{};
    for(std::size_t i = 0; i < Traits::size; ++i) {
        at(m, i) = f(v, i);
    }
    return m;
}

// Maps two vectors into a single one.
// F: (lv, rv, i) -> e.
template<typename Traits, typename F>
    constexpr
auto mapped_i(const vector<Traits>& lv, const vector<Traits>& rv, F f) {
    auto c = vector<Traits>{};
    for(std::size_t i = 0; i < Traits::size; ++i) {
        at(c, i) = f(lv, rv, i);
    }
    return c;
}

} // namespace pom
