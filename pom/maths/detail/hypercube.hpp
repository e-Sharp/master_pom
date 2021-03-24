#pragma once

#include <array>
#include <bitset>
#include <cmath>
#include <iostream>
#include <type_traits>

// Abstractions to for spatial interpolation.

// TODO: Performance profiling.
// TODO: Move to 'maths' module ?

namespace pom {
namespace maths {
namespace detail {

// TODO: Pack template parameters.
// TODO: Find a more suited name.
template<std::size_t D, typename Map, typename Reduce>
struct hypercube_object {
    static_assert(D <= 8); // Not a limitation in pratice. (unecessary ?)
    Map map;
    Reduce reduce;
};

// Factories.

template<std::size_t D, typename M, typename R>
auto hypercube(M m, R r) {
        return hypercube<D, M, R>(m, r);
}

// Compute.
// TODO: Check generated assembly code -> parameter passing.

template<std::size_t D, typename M, typename R, std::size_t I>
auto compute
    const hypercube_object<D, M, R>& h, std::bitset<D> bs,
    std::integral_constant<std::size_t, I> = {})
{
    auto rec = std::integral_constant<std::size_t, I - 1>();
    auto a = compute(h, bs, rec);
    bs.set(I - 1);
    auto b = compute(h, bs, rec);
    return h.reduce(a, b, I - 1);
}

template<std::size_t D, typename M, typename R>
auto compute(
    const hypercube_object<D, M, R>& h, std::bitset<D> bs,
    std::integral_constant<std::size_t, 0> = {})
{
    return h.map(bs);
}

template<std::size_t D, typename M, typename R>
auto compute(const hypercube_object<D, M, R>& h) {
    auto rec = std::integral_constant<std::size_t, D>();
    return compute(h, std::bitset<D>(), rec);
}

}}}
