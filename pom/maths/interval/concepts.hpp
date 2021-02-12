#pragma once

#include <cstdlib>

namespace pom {
namespace maths {

template<typename I>
concept interval = requires(const I ci) {
        // Constructors.

        { I{} };
        { I(std::size_t{}, std::size_t{}) };

        // Element access.

        { ci.lower() };
        { ci.upper() };
    };

}}
