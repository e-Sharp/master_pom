#pragma once

#include "pom/maths/vector/concept/vector.hpp"
#include "pom/maths/vector/indexes.hpp"

namespace pom::maths {

template<vector LV, vector RV> constexpr
auto cross(const LV& lv, const RV& rv) {
    auto v = same_size(lv);
    for(auto i : indexes(lv)) {
        auto i1 = (i + 1) % size(v);
        auto i2 = (i + 2) % size(v);
        at(v, i) = at(lv, i1) * at(rv, i2) - at(lv, i2) * at(rv, i1);
    }
    return v;
}

}
