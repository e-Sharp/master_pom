#pragma once

#include "concepts.hpp"

#include "pom/maths/operation/all.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace pom {
namespace maths {

// Everything shall be burned, and from the ashes, beauty will emerge.

template<matrix M, typename Index> constexpr
auto nearest_cr(const M& m, Index ci, Index ri) {
	auto c = std::min(std::max(std::size_t(std::floor(ci + 0.5f)), std::size_t{0}), col_count(m) - 1);
	auto r = std::min(std::max(std::size_t(std::floor(ri + 0.5f)), std::size_t{0}), row_count(m) - 1);
	return at_cr(m, c, r);
}

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

template<matrix M, typename Index> constexpr
auto bicubic_cr(const M& m, Index ci, Index ri) noexcept {
	auto c0 = static_cast<std::size_t>(std::min(std::max(std::floor(ci)    , Index{0}), Index(col_count(m) - 1)));
	auto c1 = static_cast<std::size_t>(std::min(std::max(std::floor(ci) + 1, Index{0}), Index(col_count(m) - 1)));
	auto r0 = static_cast<std::size_t>(std::min(std::max(std::floor(ri)    , Index{0}), Index(row_count(m) - 1)));
	auto r1 = static_cast<std::size_t>(std::min(std::max(std::floor(ri) + 1, Index{0}), Index(row_count(m) - 1)));
	auto v00 = at_cr(m, c0, r0);
	auto v01 = at_cr(m, c0, r1);
	auto v10 = at_cr(m, c1, r0);
	auto v11 = at_cr(m, c1, r1);
	return lerp(
		lerp(v00, v01, smoothstep_1(fract(ri))),
		lerp(v10, v11, smoothstep_1(fract(ri))),
		smoothstep_1(fract(ci)));
}

template<matrix M, typename Index> constexpr
auto bicubic_normalized_cr(const M& m, Index cn, Index rn) noexcept {
	auto ci = cn * (col_count(m) - 1);
	auto ri = rn * (row_count(m) - 1);
	return bicubic_cr(m, ci, ri);
}

template<matrix M, typename Index> constexpr
auto biquintic_cr(const M& m, Index ci, Index ri) noexcept {
	auto c0 = static_cast<std::size_t>(std::min(std::max(std::floor(ci)    , Index{0}), Index(col_count(m) - 1)));
	auto c1 = static_cast<std::size_t>(std::min(std::max(std::floor(ci) + 1, Index{0}), Index(col_count(m) - 1)));
	auto r0 = static_cast<std::size_t>(std::min(std::max(std::floor(ri)    , Index{0}), Index(row_count(m) - 1)));
	auto r1 = static_cast<std::size_t>(std::min(std::max(std::floor(ri) + 1, Index{0}), Index(row_count(m) - 1)));
	auto v00 = at_cr(m, c0, r0);
	auto v01 = at_cr(m, c0, r1);
	auto v10 = at_cr(m, c1, r0);
	auto v11 = at_cr(m, c1, r1);
	return lerp(
		lerp(v00, v01, smoothstep_2(fract(ri))),
		lerp(v10, v11, smoothstep_2(fract(ri))),
		smoothstep_2(fract(ci)));
}

template<matrix M, typename Index> constexpr
auto biquintic_normalized_cr(const M& m, Index cn, Index rn) noexcept {
	auto ci = cn * (col_count(m) - 1);
	auto ri = rn * (row_count(m) - 1);
	return biquintic_cr(m, ci, ri);
}

}}
