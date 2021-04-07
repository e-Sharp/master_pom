#pragma once

#include "pom/terrain/function/concept/function.hpp"
#include "pom/terrain/function/opposed/all.hpp"

namespace pom::terrain {

template<function F> constexpr
auto operator-(F&& f) {
	return opposed(std::forward<F>(f));
}

}
