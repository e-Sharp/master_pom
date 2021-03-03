#pragma once

#include "concepts.hpp"

#include "pom/maths/fract.hpp"
#include "pom/maths/interpolation.hpp"

#include <cmath>

namespace pom {
namespace maths {

template<matrix M, typename Index> constexpr
auto bilerp_cr(const M& m, Index ci, Index ri) noexcept {
	auto c0 = static_cast<std::size_t>(std::min(std::max(std::floor(ci)    , Index{0}), Index(col_count(m) - 1)));
	auto c1 = static_cast<std::size_t>(std::min(std::max(std::floor(ci) + 1, Index{0}), Index(col_count(m) - 1)));
	auto r0 = static_cast<std::size_t>(std::min(std::max(std::floor(ri)    , Index{0}), Index(row_count(m) - 1)));
	auto r1 = static_cast<std::size_t>(std::min(std::max(std::floor(ri) + 1, Index{0}), Index(row_count(m) - 1)));
	auto v00 = at_cr(m, c0, r0);
	auto v01 = at_cr(m, c0, r1); 
	auto v10 = at_cr(m, c1, r0);
	auto v11 = at_cr(m, c1, r1);
	return lerp(lerp(v00, v01, fract(ri)), lerp(v10, v11, fract(ri)), fract(ci));
}

template<matrix M, typename Index> constexpr
auto bilerp_normalized_cr(const M& m, Index cn, Index rn) noexcept {
	auto ci = cn * (col_count(m) - 1);
	auto ri = rn * (row_count(m) - 1);
	return bilerp_cr(m, ci, ri);
}

}}
