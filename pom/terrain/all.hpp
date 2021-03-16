#pragma once

#include "primitive/all.hpp"
#include "paths.hpp"
#include "wavefront.hpp"

#include "pom/maths_impl/all.hpp"
#include "pom/terrain/heightfield.hpp"
#include "pom/terrain/tesselation.hpp"

#include "effect/erosion.hpp"
#include "primitive/all.hpp"

namespace pom {
namespace terrain {

using point = maths_impl::static_vector<float, 2>;

struct eval {
    float value = {};
    float weight = {};
};

template<typename TL, typename TR, typename F> constexpr
auto combination(const TL& lsubtree, const TR& rsubtree, F f) noexcept {
    return [=](point p) {
        return f(lsubtree(p), rsubtree(p));
    };
}

template<typename T, typename F> constexpr
auto modulation(const T& subtree, F f) noexcept {
    return [=](point p) {
        return f(subtree(p));
    };
}

template<typename T, typename F> constexpr
auto warping(const T& subtree, F f) noexcept {
    return [=](point p) {
        return subtree(f(p));
    };
}

}}
