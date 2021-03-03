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

	
	matrix heights = {};

	maths_impl::interval<float> x_domain = maths_impl::interval_0_1<float>();
	maths_impl::interval<float> y_domain = maths_impl::interval_0_1<float>();
};

constexpr auto ci_to_x_mapping(const heightfield& hf) {
	return maths::mapping(
		maths_impl::interval_0_n(col_count(hf.heights)), hf.x_domain);
}

constexpr auto ri_to_y_mapping(const heightfield& hf) {
	return maths::mapping(
		maths_impl::interval_0_n(row_count(hf.heights)), hf.y_domain);
}

}}
