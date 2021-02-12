#pragma once

#include <concepts>
#include <cstdlib>

namespace pom {
namespace maths {

template<typename V>
concept vector = requires {
    // Constructors.

    { V{} };
    { V(std::size_t{}) };
} && requires(const V v) {
    // Element access.

    { at(v, std::size_t{}) };

    // Iterators.

    { begin(v) };
    { end(v) };

    // Capacity.

    { size(v) } -> std::same_as<std::size_t>;
} && requires(V v) {
    // Element access.

	{ at(v, std::size_t{}) };

    // Iterators.

    { begin(v) };
    { end(v) };
};

}}
