#pragma once

#include "dot.hpp"

#include <cmath>

namespace pom::maths {

template<vector V>
auto length(const V& v) {
    return std::sqrt(dot(v, v));
}

}
