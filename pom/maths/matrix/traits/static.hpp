#pragma once

#include "pom/maths/annotation/dimension.hpp"
#include "pom/maths/matrix/traits/matrix.hpp"

#include <array>

namespace pom {

template<typename Ty>
concept static_matrix_traits =
	matrix_traits<Ty> &&
	Ty::is_static;

template<typename Ty, col CCount, row RCount>
struct default_static_matrix_traits {
	static constexpr auto is_static = true;

	struct storage {

	};
};

} // namespace pom
