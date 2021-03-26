#pragma once

#include <pom/maths/vector/all.hpp>

namespace pom::terrain {

template<typename Ty, std::size_t N>
struct vec : maths::static_vector<Ty, N> {
	constexpr vec() {}

	constexpr vec(Ty v) {
		for(auto& e : *this) e = v;
	}

	template<std::size_t = N> requires(N == 2)
	constexpr vec(Ty x, Ty y) {
		at(*this, 0) = x;
		at(*this, 1) = y;
	}

	template<std::size_t = N> requires(N == 3)
	constexpr vec(Ty x, Ty y, Ty z) {
		at(*this, 0) = x;
		at(*this, 1) = y;
		at(*this, 2) = z;
	}
};

template<typename Ty>
vec(Ty, Ty) -> vec<Ty, 2>;

using vec2f = vec<float, 2>;
using vec3f = vec<float, 3>;

}
