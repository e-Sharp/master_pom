#pragma once

#include "distortion.hpp"

#include "pom/terrain/function/concept/first_order_function.hpp"

namespace pom::terrain {

template<typename Terrain>
struct distorted {
	distortion distortion;
	Terrain terrain;
};

template<typename T>
distorted(distortion, T&&) -> distorted<T>;

template<typename... D>
struct is_first_order_function<distorted<D...>>
: std::true_type {};

}
