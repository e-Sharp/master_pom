#pragma once

#include "pom/maths/matrix/all.hpp"
#include "pom/maths_impl/all.hpp"

namespace pom {
namespace terrain {

using domain = maths_impl::static_vector<maths_impl::interval<float>, 2>;

//template<typename Terrain, maths::vector V>
//maths_impl::static_vector_<float, 2>  gradient(Terrain t, V v) {
//	auto e = 0.01f;
//	auto dx = (t(x + e, y    ) - t(x - e, y    )) / (2.f * e);
//	auto dy = (t(x    , y + e) - t(x    , y - e)) / (2.f * e);
//}

template<typename Terrain>
maths_impl::dynamic_matrix<maths_impl::static_vector<float, 2>> gradients(Terrain t, const domain& d, std::size_t resolution) {
	auto ra = maths_impl::interval{std::size_t{0}, resolution - 1};
	auto c_to_x = maths::mapping(ra, at(d, 0));
	auto r_to_y = maths::mapping(ra, at(d, 1));
	auto m = maths_impl::dynamic_matrix<maths_impl::static_vector<float, 2>>(resolution);
	for(auto r : maths::row_indexes(m)) {
		auto y = r_to_y(r);
		for(auto c : maths::col_indexes(m)) {
			auto x = c_to_x(c);
			auto e = 0.01f;
			auto dx = (t(x + e, y    ) - t(x - e, y    )) / (2.f * e);
			auto dy = (t(x    , y + e) - t(x    , y - e)) / (2.f * e);
			at(at(m, r), c) = {dx, dy};
		}
	}
	return m;
}

template<typename Terrain>
maths_impl::dynamic_matrix<float> tesselation(Terrain t, const domain& d, std::size_t resolution) {
	auto ra = maths_impl::interval{std::size_t{0}, resolution - 1};
	auto c_to_x = maths::mapping(ra, at(d, 0));
	auto r_to_y = maths::mapping(ra, at(d, 1));
	auto m = maths_impl::dynamic_matrix<float>({maths_impl::row{resolution}, maths_impl::col{resolution}});
	for(auto r : maths::row_indexes(m)) {
		auto y = r_to_y(r);
		for(auto c : maths::col_indexes(m)) {
			auto x = c_to_x(c);
			at(at(m, r), c) = t(x, y);
		}
	}
	return m;
}

}}
