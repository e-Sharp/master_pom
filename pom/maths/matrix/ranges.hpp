#pragma once

#include "concepts.hpp"

#include <range/v3/view/cartesian_product.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>

#include <tuple>

namespace pom {
namespace maths {

// Single indexes.

template<typename M> constexpr
auto col_indexes(const M& m) {
	auto cc = col_count(m);
	return ranges::views::iota(decltype(cc){0}, cc);
}

template<typename M> constexpr
auto row_indexes(const M& m) {
	auto rc = row_count(m);
	return ranges::views::iota(decltype(rc){0}, rc);
}

// Full indexes.

// TODO: col_major_indexes_cr.
// TODO: col_major_indexes_rc.

template<typename M> constexpr
auto row_major_indexes_rc(const M& m) {
	return ranges::views::cartesian_product(row_indexes(m), col_indexes(m));
}

template<typename M> constexpr
auto row_major_indexes_cr(const M& m) {
	return row_major_indexes_rc(m)
	| ranges::views::transform([](auto rc) {
		auto&& [r, c] = rc;
		return std::make_tuple(c, r);
	});
}

// Elements.

// TODO: Check element counts.
//template<typename... Ms> constexpr
//auto row_major(Ms&&... matrices) {
//	return ranges::views::zip(row_major(std::forward<Ms>(matrices))...);
//}

}}
