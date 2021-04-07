#pragma once

#include "scaled.hpp"
#include "scaling.hpp"

#include "pom/terrain/function/concept/function.hpp"

namespace pom::terrain {

template<function F> constexpr
auto operator|(F&& f, scaling s) {
	return scaled(std::move(s), std::forward<F>(f));
}

}
