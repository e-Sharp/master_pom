#include "pom/maths_impl/all.hpp"

#include <iostream>

using namespace pom;
using namespace pom::maths_impl;

int main() {
	auto c = col(4);
	auto r = row(3);
	auto m = maths_impl::dynamic_matrix<float>({r, c});
}
