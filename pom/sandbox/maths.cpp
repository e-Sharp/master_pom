#include "pom/maths/matrix/interpolation.hpp"
#include "pom/maths_impl/all.hpp"

#include <iostream>
#include <range/v3/all.hpp>
#include <vector>

using namespace pom;
using namespace pom::maths_impl;

int main() {
	auto m = maths_impl::matrix<float>(2);
	at(m, col(0), row(0)) = 0.f;
	at(m, col(0), row(1)) = 1.f;
	at(m, col(1), row(0)) = 1.f;
	at(m, col(1), row(1)) = 2.f;
	for(auto i = 0.f; i < 1.f; i += 0.1f) {
		std::cout << bilerp(m, maths::col_i(i), maths::row_i(0.5f)) << std::endl;
	}
}
