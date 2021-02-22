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

}}
