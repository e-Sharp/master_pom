#pragma once

#include "concepts.hpp"

#include <range/v3/view/for_each.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/zip.hpp>
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
// TODO: row_major_indexes_cr.
// TODO: row_major_indexes_rc.

// Elements.

// TODO: Check element counts.
//template<typename... Ms> constexpr
//auto row_major(Ms&&... matrices) {
//	return ranges::views::zip(row_major(std::forward<Ms>(matrices))...);
//}

}}
