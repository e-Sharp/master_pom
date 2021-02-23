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
auto matrix(col_i ccount, row_i rcount) {
	return dynamic_matrix<Ty>(ccount, rcount);
}

template<typename Ty> constexpr
auto matrix(row_i rcount, col_i ccount) {
	return dynamic_matrix<Ty>(rcount, ccount);
}

template<typename Ty> constexpr
auto matrix(std::size_t square) {
	return dynamic_matrix<Ty>(square);
}

// Imitation factories.

template<typename DTy, typename STy> constexpr
auto same_size_matrix(const dynamic_matrix<STy>& m) {
	return dynamic_matrix<DTy>(col(col_count(m)), row(row_count(m)));
}

template<typename Ty> constexpr
auto same_size_matrix(const dynamic_matrix<Ty>& m) {
	return same_size_matrix<Ty, Ty>(m);
}

}}
