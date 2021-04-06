#pragma once

#include "composed.hpp"

#include "pom/terrain/function/concept/function.hpp"
#include "pom/terrain/function/concept/higher_order_function.hpp"

namespace pom::terrain {

template<function First, higher_order_function Second> constexpr
auto operator|(First&& f, Second&& s) {
	return composed(
		std::forward<First>(f),
		std::forward<Second>(s));
}

}
