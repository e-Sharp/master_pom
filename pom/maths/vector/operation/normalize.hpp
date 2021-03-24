#pragma once

#include <pom/meta/exception/all.hpp>
#include <pom/meta/tag/all.hpp>

namespace pom::maths {

template<vector V>
auto normalized(const V& v, meta::unchecked) {
    return v / length(v);
}

template<vector V>
auto normalized(const V& v, meta::checked = {}) {
    auto l = length(v);
    if(l == 0) throw meta::precondition_violation(); // Use an epsilon ?
    return v / l;
}

}
