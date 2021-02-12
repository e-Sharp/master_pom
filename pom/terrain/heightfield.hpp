#pragma once

#include "pom/maths/matrix/all.hpp"
#include "pom/maths_impl/all.hpp"

namespace pom {
namespace terrain {

struct heightfield {
	using interval = maths_impl::interval_<float>;
	using matrix = maths_impl::dynamic_matrix_<float>;
	template<typename Ty, std::size_t S>
	using vector = maths_impl::static_vector_<Ty, S>;

	vector<interval, 2> domain = {};
	matrix heights = {};
};

}}
