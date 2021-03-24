#pragma once

#include "heightfield.hpp"

#include "pom/maths/matrix/all.hpp"
#include "pom/maths/all.hpp"

namespace pom {
namespace terrain {

using domain = maths::static_vector<maths::interval<float>, 2>;

template<typename Terrain>
auto gradients(Terrain t, const heightfield& hf, std::size_t resolution) {
	auto m = maths::dynamic_matrix<maths::static_vector<float, 2>>(resolution);
	auto ci_to_x = ci_to_x_mapping(hf);
	auto ri_to_y = ri_to_y_mapping(hf);
	for(auto ri : maths::row_indexes(m)) {
		auto y = ri_to_y(ri);
		for(auto ci : maths::col_indexes(m)) {
			auto x = ci_to_x(ci);
			auto e = 0.01f;
			auto dx = (t(x + e, y    ) - t(x - e, y    )) / (2.f * e);
			auto dy = (t(x    , y + e) - t(x    , y - e)) / (2.f * e);
			at_cr(m, ci, ri) = {dx, dy};
		}
	}
	return m;
}

template<typename Terrain>
maths::dynamic_matrix<float> tesselation(Terrain t, const heightfield& hf, std::size_t resolution) {
	auto m = maths::dynamic_matrix<float>(resolution);
	auto ci_to_x = ci_to_x_mapping(hf);
	auto ri_to_y = ri_to_y_mapping(hf);
	for(auto ri : maths::row_indexes(m)) {
		auto y = ri_to_y(ri);
		for(auto ci : maths::col_indexes(m)) {
			auto x = ci_to_x(ci);
			at_cr(m, ci, ri) = t(x, y);
		}
	}
	return m;
}



}}
