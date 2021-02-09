#pragma once

#include <cstdlib>

namespace pom {
namespace maths {

template<typename I>
concept interval =
    requires {
        // Constructors.

        { I{} };
        { I(std::size_t{}, std::size_t{}) };
    } && requires(const I i) {
        // Element access.

        { i.lower() };
        { i.upper() };
    };

}}
