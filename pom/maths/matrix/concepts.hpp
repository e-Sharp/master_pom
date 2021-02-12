#pragma once

#include "pom/maths/vector/concepts.hpp"

#include <concepts>
#include <cstdlib>

namespace pom {
namespace maths {

template<typename Matrix>
concept matrix = requires(const Matrix cm, Matrix m) {
	// Constructors.

	{ Matrix{} };
    { Matrix({std::size_t{}, std::size_t{}}) };

	// Capacity.

	{ size(cm) } -> vector;

	// Element access.

	{ at(cm, {std::size_t{}, std::size_t{}}) };
	{ at(m, {std::size_t{}, std::size_t{}}) };
};

}}
