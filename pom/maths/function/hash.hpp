#pragma once

#include "pom/maths/function/fract.hpp"
#include "pom/maths/vector/all.hpp"

#include <iostream>

namespace pom {

template<typename Traits> constexpr
vector<Traits> hash(vector<Traits> v) {
    auto k = vector<Traits>{0.3183099f, 0.3678794f};
    v = v * k + vector<Traits>{at(k, 1), at(k, 0)};
    auto h = -1.0 + 2.0 * fract(16.0 * k * fract(at(v, 0) * at(v, 1) * (at(v, 0) + at(v, 1))));
    // std::cout << at(v, 0) << " " << at(v, 1) << " " << at(h, 0) << " " << at(h, 1) << std::endl;
    return h;
}

} // namespace pom
