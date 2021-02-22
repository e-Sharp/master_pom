#pragma once

#include <concepts>
#include <cstdlib>

namespace pom {
namespace maths {

template<typename C> constexpr
auto size(const C& c) -> decltype(c.size()) {
    return c.size();
}

template<typename V>
concept vector = requires(const V cv, V v) {
    // Types.

    // typename V::index_type;

    // Element access.

    at(v, std::size_t{});

    // Iterators.

    //begin(v);
    //end(v);

    // Capacity.

    size(v);
};

}}
