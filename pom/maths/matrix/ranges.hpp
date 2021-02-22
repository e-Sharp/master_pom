#pragma once

#include "concepts.hpp"

#include <range/v3/view/for_each.hpp>
#include <range/v3/view/iota.hpp>
#include <tuple>

namespace pom {
namespace maths {

template<typename M> constexpr
auto col_indexes(const M& m) {
	auto cc = col_count(m);
	return ranges::views::ints(decltype(cc){0}, cc);
}

template<typename M> constexpr
auto row_indexes(const M& m) {
	auto rc = row_count(m);
	return ranges::views::ints(decltype(rc){0}, rc);
}

//

template<matrix M> constexpr
auto row_major_indexes(const M& m) {
	auto cis = col_indexes(m);
	return ranges::views::for_each(row_indexes(m), [cis](auto r) {
		return ranges::views::transform(cis, [r](auto c) {
			return std::make_tuple(c, r); }); });
}

}}
