#pragma once

#include "col_row.hpp"

#include "pom/maths/vector/concepts.hpp"

#include <concepts>
#include <cstdlib>

namespace pom {
namespace maths {

template<typename C> constexpr
auto col_count(const C& c) -> decltype(c.col_count()) {
	return c.col_count();
}

template<typename C> constexpr
auto row_count(const C& c) -> decltype(c.row_count()) {
	return c.row_count();
}

template<typename Matrix>
concept matrix = true;

}}
