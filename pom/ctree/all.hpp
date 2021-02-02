#pragma once

#include "pom/maths/preset/default/all.hpp"

namespace pom {
namespace ctree {

using point = pom::maths::default_preset::static_vector<float, 2>;

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
