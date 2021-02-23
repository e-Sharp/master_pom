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
	return ranges::views::iota(decltype(cc){0}, cc);
}

template<typename M> constexpr
auto row_indexes(const M& m) {
	auto rc = row_count(m);
	return ranges::views::iota(decltype(rc){0}, rc);
}

}}
