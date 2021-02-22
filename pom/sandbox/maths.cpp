#include "pom/maths/matrix/all.hpp"
#include "pom/maths_impl/matrix.hpp"

#include <iostream>

using namespace pom;
using namespace pom::maths_impl;

int main() {
	auto m = matrix<float>(4, 3);
	for(auto [c, r] : maths::row_major_indexes(m)) {
		std::cout << "(" << c << " " << r << ")" << std::endl;
	}
	
}
