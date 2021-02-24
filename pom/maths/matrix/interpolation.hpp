#pragma once

#include "concepts.hpp"

#include "pom/maths/fract.hpp"
#include "pom/maths/interpolation.hpp"

#include <cmath>

namespace pom {
namespace maths {

template<matrix M, typename I>
auto bilerp(const M& m, col_i<I> ci, row_i<I> ri) noexcept {
	auto c0 = static_cast<std::size_t>(std::min(std::max(std::floor(I{ci})    , I{0}), I(col_count(m) - 1)));
	auto c1 = static_cast<std::size_t>(std::min(std::max(std::floor(I{ci}) + 1, I{0}), I(col_count(m) - 1)));
	auto r0 = static_cast<std::size_t>(std::min(std::max(std::floor(I{ri})    , I{0}), I(row_count(m) - 1)));
	auto r1 = static_cast<std::size_t>(std::min(std::max(std::floor(I{ri}) + 1, I{0}), I(row_count(m) - 1)));
	auto v00 = at(m, col_i(c0), row_i(r0));
	auto v01 = at(m, col_i(c0), row_i(r1)); 
	auto v10 = at(m, col_i(c1), row_i(r0));
	auto v11 = at(m, col_i(c1), row_i(r1));
	return lerp(
		lerp(v00, v01, fract(I{ri})),
		lerp(v10, v11, fract(I{ri})),
		fract(I{ci}));
}

}}
