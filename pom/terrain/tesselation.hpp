#pragma once

#include "pom/maths/matrix/all.hpp"
#include "pom/maths_impl/all.hpp"

namespace pom {
namespace terrain {

using domain = maths_impl::static_vector_<maths_impl::interval_<float>, 2>;

template<typename Terrain>
dynamic_matrix<float> tesselation(Terrain t, const domain& d, std::size_t resolution) {
	auto range = maths_impl::interval_{0.f, static_cast<float>(resolution - 1)};
	auto c_to_x = maths::mapping(range, at(d, 0));
	auto r_to_y = maths::mapping(range, at(d, 1));
	auto m = dynamic_matrix<float>{col{resolution}, row{resolution}};
	for(row r = {0}; r < resolution; ++r) {
		auto y = r_to_y(r);
		for(col c = {0}; c < resolution; ++c) {
			auto x = c_to_x(c);
			at(m, c, r) = t(x, y);
		}
	}
	return m;
}

}}
