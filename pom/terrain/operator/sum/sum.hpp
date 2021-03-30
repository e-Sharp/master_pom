#pragma once

#include "sum_operation.hpp"

#include <tuple>

namespace pom::terrain {

struct sum {};

template<typename Terrain, typename... Terrains> constexpr
auto sum_of(Terrain&& t, Terrains&&... ts) {
	return sum_operation(
		std::forward<Terrain>(t),
		sum_of(std::forward<Terrains>(ts)...));
}

template<typename Terrain> constexpr
auto sum_of(Terrain&& t) {
	return std::forward<Terrain>(t);
}

template<typename... T> constexpr
auto operator|(std::tuple<T...>&& t, sum) {
	return std::apply(
		[](auto&&... args) { 
			return sum_of(std::forward<decltype(args)>(args)...); },
		std::move(t));
}

}
