#pragma once

#include "pom/terrain/operator/operation.hpp"

namespace pom::terrain {

template<operation First, operation Second>
struct composed {
	First first;
	Second second;
};

template<typename F, typename S>
composed(F&&, S&&) -> composed<F, S>;

template<typename... C>
struct is_operation<composed<C...>> {
	static constexpr bool value = true;
};

template<typename Terrain, typename... C> constexpr
auto operator|(Terrain&& t, composed<C...>&& c) {
	return std::move(t) | std::move(c.first) | std::move(c.second);
}

template<operation F, operation S>
auto operator|(F&& f, S&& s) {
	return composed(std::move(f), std::move(s));
}

}
