#pragma once

#include "pom/maths/interval/all.hpp"
#include "pom/maths/matrix/all.hpp"
#include "pom/maths_impl/all.hpp"

namespace pom {
namespace terrain {

struct heightfield {
	using interval = maths_impl::interval<float>;
	using matrix = maths_impl::dynamic_matrix<float>;
	template<typename Ty, std::size_t S>
	using vector = maths_impl::static_vector<Ty, S>;

	vector<interval, 2> domain = {};
	matrix heights = {};
};

constexpr auto col_to_x_mapping(const heightfield& hf) {
	return maths::mapping(
		maths_impl::interval_0_n(col_count(hf.heights) - 1),
		at(hf.domain, 0));
}

constexpr auto row_to_y_mapping(const heightfield& hf) {
	return maths::mapping(
		maths_impl::interval_0_n(row_count(hf.heights) - 1),
		at(hf.domain, 1));
}

}}
