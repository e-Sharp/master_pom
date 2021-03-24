#pragma once

#include "pom/terrain/import/all.hpp"

#include <pom/maths/all.hpp>

namespace pom::terrain {

struct heightfield {
	mat<float> heights = {};

	interval<float> x_domain = maths::interval_0_1<float>();
	interval<float> y_domain = maths::interval_0_1<float>();
	interval<float> u_domain = maths::interval_0_1<float>();
	interval<float> v_domain = maths::interval_0_1<float>();
};

constexpr auto ci_to_x_mapping(const heightfield& hf) {
	return maths::mapping(
		maths::interval_0_n(col_count(hf.heights)), hf.x_domain);
}

constexpr auto ri_to_y_mapping(const heightfield& hf) {
	return maths::mapping(
		maths::interval_0_n(row_count(hf.heights)), hf.y_domain);
}

constexpr auto ci_to_u_mapping(const heightfield& hf) {
	return maths::mapping(
		maths::interval_0_n(col_count(hf.heights)), hf.u_domain);
}

constexpr auto ri_to_v_mapping(const heightfield& hf) {
	return maths::mapping(
		maths::interval_0_n(row_count(hf.heights)), hf.v_domain);
}

}
