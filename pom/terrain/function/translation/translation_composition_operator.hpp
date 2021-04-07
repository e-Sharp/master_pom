#pragma once

#include "translated.hpp"
#include "translation.hpp"

#include "pom/terrain/function/concept/first_order_function.hpp"

namespace pom::terrain {

template<first_order_function F> constexpr
auto operator|(F&& f, translation t) {
	return translated(std::move(t), std::forward<F>(f));
}

}
