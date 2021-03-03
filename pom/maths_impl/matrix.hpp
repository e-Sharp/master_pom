#pragma once

#include "dynamic_matrix.hpp"
#include "matrix_view.hpp"

#include <range/v3/view/drop.hpp>
#include <range/v3/view/for_each.hpp>

namespace pom {
namespace maths_impl {

// Dynamic matrix factories.

template<typename Ty> constexpr
auto matrix() {
	return dynamic_matrix<Ty>();
}

template<typename Ty> constexpr
auto matrix_cr(std::size_t c, std::size_t r) {
	return dynamic_matrix<Ty>(maths::col_i(c), maths::row_i(r));
}

template<typename Ty> constexpr
auto matrix(std::size_t square) {
	return dynamic_matrix<Ty>(square);
}

// Imitation factories.

template<typename DTy, typename STy> constexpr
auto same_size_matrix(const dynamic_matrix<STy>& m) {
	return dynamic_matrix<DTy>(
		maths::col_i(col_count(m)), maths::row_i(row_count(m)));
}

template<typename Ty> constexpr
auto same_size_matrix(const dynamic_matrix<Ty>& m) {
	return same_size_matrix<Ty, Ty>(m);
}

// Views.

template<typename Ty> constexpr
auto view(dynamic_matrix<Ty>& m) {
	return matrix_view(
		row_major(m),
		maths::col_i(col_count(m)),
		maths::row_i(row_count(m)));
}

template<typename Ty> constexpr
auto view_cr(
	dynamic_matrix<Ty>& m,
	static_vector<std::size_t, 2> offset,
	static_vector<std::size_t, 2> size)
{
	auto r = ranges::views::for_each(
		row_major(m) | ranges::views::chunk(col_count(m))
		| ranges::views::drop(at(offset, 1))
		| ranges::views::take(at(size, 1)),
		[&](auto&& row) {
			return row
			| ranges::views::drop(at(offset, 0))
			| ranges::views::take(at(size, 0));
		}
	);
	return matrix_view(
		std::move(r),
		maths::col_i(at(size, 0)),
		maths::row_i(at(size, 1)));
}

}}
