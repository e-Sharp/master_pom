#pragma once

#include "color.hpp"

#include "pom/terrain/coloration/colored/colored.hpp"

namespace pom::terrain {

template<typename F> constexpr
auto operator|(F&& f, color c) {
	return colored(std::move(c), std::forward<F>(f));
}

}
