#pragma once

#include "pom/maths/matrix/col_row.hpp"

#include <concepts>
#include <cstdlib>

namespace pom {
namespace maths_impl {

using col = maths::col<std::size_t>;
using row = maths::row<std::size_t>;

struct col_row {
	col col = {};
	row row = {};
};

struct row_col {
	row row = {};
	col col = {};
};

}}
