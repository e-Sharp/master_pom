#pragma once

#include "dynamic_matrix.hpp"

namespace pom {
namespace maths_impl {

// Dynamic matrix.

template<typename Ty> constexpr
auto matrix() noexcept {
	return dynamic_matrix<Ty>{};
}

template<typename Ty> constexpr
auto matrix(std::size_t rows, std::size_t cols) {
	return dynamic_matrix<Ty>(rows, cols);
}

//

template<typename DTy, typename STy> constexpr
auto same_size(const dynamic_matrix<STy>& m) {
	return dynamic_matrix<DTy>(m.row_count(), m.col_count());
}

template<typename Ty> constexpr
auto same_size(const dynamic_matrix<Ty>& m) {
	return dynamic_matrix<Ty>(m.row_count(), m.col_count());
}

}}
