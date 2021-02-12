#include "pom/maths/matrix/concepts.hpp"
#include "pom/maths_impl/dynamic_matrix.hpp"

#include <iostream>

using namespace pom::maths_impl;

int main() {
	auto m = dynamic_matrix_<float>({4, 3});
	auto s = size(m);
	for(decltype(s) ij = {0, 0}; at(ij, 1) < at(s, 1); ++at(ij, 1)) {
		for(at(ij, 0) = 0; at(ij, 0) < at(s, 0); ++at(ij, 0)) {
			std::cout << "(" << at(ij, 0) << ", " << at(ij, 1) << ") ";
		}
		std::cout << std::endl;
	}
}
