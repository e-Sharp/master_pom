#pragma once

#include "dynamic_matrix.hpp"

namespace pom {
namespace maths_impl {

// Dynamic matrix factories.

template<typename Ty> constexpr
auto matrix() noexcept {
	return dynamic_matrix<Ty>{};
}

template<typename Ty> constexpr
auto matrix(std::size_t rows, std::size_t cols) {
	return dynamic_matrix<Ty>({maths::row{rows}, maths::col{cols}});
}

// Imitation factories.

template<typename DTy, typename STy> constexpr
auto same_size_matrix(const dynamic_matrix<STy>& m) {
	return dynamic_matrix<DTy>(m.size());
}

template<typename Ty> constexpr
auto same_size_matrix(const dynamic_matrix<Ty>& m) {
	return same_size_matrix<Ty, Ty>(m);
}

}}
