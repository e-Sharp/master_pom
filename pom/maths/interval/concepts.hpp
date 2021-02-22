#pragma once

#include <cstdlib>

namespace pom {
namespace maths {

template<typename C> constexpr
auto lower(const C& c) -> decltype(c.lower()) {
    return c.lower();
}

template<typename C> constexpr
auto upper(const C& c) -> decltype(c.upper()) {
    return c.upper();
}

template<typename I>
concept interval = requires(const I ci) {
    // Constructors.

    { I{} };
    { I(lower(ci), upper(ci)) };

    // Element access.

    { ci.lower() };
    { ci.upper() };
};

}}
