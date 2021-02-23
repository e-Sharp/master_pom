#pragma once

#include "col_row_indexes.hpp"

#include "pom/maths/vector/concepts.hpp"

#include <concepts>
#include <cstdlib>

namespace pom {
namespace maths {

template<typename Matrix>
concept matrix = requires(const Matrix& cm, Matrix& m) {
	// Ordering.

	// TODO correctly.

	// Size.

	col_count(cm);
	row_count(cm);

	// Element ranges.

	col_major(cm);
	col_major(m);
	row_major(cm);
	row_major(m);

	// Vector access.

	{ col(cm, col_count(cm)) } ->vector;
	{ col(m, col_count(m)) } -> vector;
	{ row(cm, row_count(cm)) } -> vector;
	{ row(m, row_count(m)) } -> vector;
};

}}
