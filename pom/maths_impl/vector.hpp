#pragma once

#include "static_vector.hpp"

#include <type_traits>

namespace pom {
namespace maths_impl {

// Static vector.

template<typename Ty, std::size_t N> constexpr
auto vector() {
	return static_vector<Ty, N>();
}

template<typename Ty, std::size_t N> constexpr
auto vector(std::size_t n) {
	return static_vector<Ty, N>(n);
}

template<std::size_t N, typename Ty> constexpr
auto vector(std::initializer_list<Ty> l) {
	return static_vector<Ty, N>(l);
}

// Imitation factories.

template<typename DTy, typename STy, std::size_t N> constexpr
auto same_size(static_vector<STy, N>) {
	return static_vector<DTy, N>();
}

template<typename Ty, std::size_t N> constexpr
auto same_size(const static_vector<Ty, N>& v) {
	return same_size<Ty, Ty>(v);
}

// Doesn't make a copy. Should reflect that somehow. meta::defaulted tag ?
template<std::size_t DN, typename Ty, std::size_t SN> constexpr
auto similar(const static_vector<Ty, SN>&) {
	return static_vector<Ty, DN>();
}

}}
