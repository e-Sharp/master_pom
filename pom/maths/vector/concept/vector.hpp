#pragma once

#include <cstdlib>

namespace pom::maths {

template<typename V>
concept vector = requires(const V cv, V v) {
    at(v, std::size_t{});
    size(v);
};

}
