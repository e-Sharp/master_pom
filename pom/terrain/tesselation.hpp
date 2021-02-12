#pragma once

#include "pom/maths/matrix/all.hpp"
#include "pom/maths_impl/all.hpp"

namespace pom {
namespace terrain {

using domain = maths_impl::static_vector_<maths_impl::interval_<float>, 2>;

template<typename Terrain>
maths_impl::dynamic_matrix_<float> tesselation(Terrain t, const domain& d, std::size_t resolution) {
	auto range = maths_impl::interval_{0.f, static_cast<float>(resolution - 1)};
	auto c_to_x = maths::mapping(range, at(d, 0));
	auto r_to_y = maths::mapping(range, at(d, 1));
	auto m = maths_impl::dynamic_matrix_<float>({resolution, resolution});
	for(std::size_t j = 0; j < at(size(m), 1); ++j) {
		auto y = r_to_y(j);
		for(std::size_t i = 0; i < at(size(m), 0); ++i) {
			auto x = c_to_x(i);
			at(m, {i, j}) = t(x, y);
		}
	}
	return m;
}

}}
