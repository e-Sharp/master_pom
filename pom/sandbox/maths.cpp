#include "pom/maths/matrix/all.hpp"
#include "pom/maths/vector/all.hpp"
#include "pom/maths_impl/all.hpp"
#include "pom/terrain/imports.hpp"

#include <iomanip>
#include <iostream>
#include <range/v3/all.hpp>
#include <vector>

using namespace pom;
using namespace pom::maths_impl;
using namespace pom::terrain;
using namespace ranges;

int main() {
	auto m = matrix_cr<float>(2, 2);
	at_cr(m, 0, 0) = 0;
	at_cr(m, 1, 0) = 1;
	at_cr(m, 0, 1) = 0;
	at_cr(m, 1, 1) = 1;
	std::cout << std::fixed;
	for(auto j = 0.f; j <= 1.f; j += 0.1f)
	for(auto c = 0.f; c <= 1.f; c += 0.1f) {
		std::cout << i << " " << maths::bicubic_normalized_cr(m, i, 0.5f) << " " << maths::bicubic_normalized_cr(m, i, 0.f) << " " << maths::bicubic_normalized_cr(m, i, 1.f) << "\n";
	}
}
