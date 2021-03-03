#include "pom/maths/vector/all.hpp"
#include "pom/maths_impl/all.hpp"

#include <iomanip>
#include <iostream>
#include <range/v3/all.hpp>
#include <vector>

using namespace pom;
using namespace pom::maths_impl;
using namespace ranges;

int main() {
	auto v = std::vector<int>{-1, -2, -3, -4};
	for(auto&& [f, s] : views::enumerate(v)) {
		std::cout << s << std::endl;
	}
}
