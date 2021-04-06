#pragma once

#include "composed.hpp"

#include "pom/terrain/function/concept/function.hpp"
#include "pom/terrain/function/concept/higher_order_function.hpp"

namespace pom::terrain {

template<function F, typename... C> constexpr
auto operator|(F&& f, composed<C...>&& c) {
	return std::forward<F>(f) | std::move(c.first) | std::move(c.second);
}

}
