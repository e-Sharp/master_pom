#pragma once

#include "distorted.hpp"
#include "distortion.hpp"

#include "pom/terrain/function/concept/first_order_function.hpp"

namespace pom::terrain {

template<first_order_function F> constexpr
auto operator|(F&& f, distortion d) {
	return distorted(std::move(d), std::forward<F>(f));
}

}
