#pragma once

#include "pom/maths/vector/all.hpp"

#include <cmath>

namespace pom {

float fract(float x) noexcept {
    return x - std::floor(x);
}

template<typename Tr>
vector<Tr> fract(const vector<Tr>& v) noexcept {
    const auto m = [](const vector<Tr>& v, std::size_t i) {
        return fract(at(v, i));
    };
    return mapped_i(v, m);
}

} // namespace pom
