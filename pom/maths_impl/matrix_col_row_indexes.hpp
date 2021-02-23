#pragma once

#include "pom/maths/matrix/col_row_indexes.hpp"

#include <concepts>
#include <cstdlib>

namespace pom {
namespace maths_impl {

using col_i = maths::col_i<std::size_t>;
using row_i = maths::row_i<std::size_t>;

constexpr col_i col(std::size_t i) noexcept {
	return col_i{i};
}

constexpr row_i row(std::size_t i) noexcept {
	return row_i{i};
}

}}
