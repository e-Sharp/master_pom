#include "pom/maths/function/vector/all.hpp"
#include "pom/maths/preset/default/all.hpp"

#include <iostream>

using namespace pom::maths;
using namespace default_preset;

void throwing_main() {
	auto v = static_vector<int, 3>{{1, 2, 3}};
	auto vv = dot(v, v);
	std::cout << vv << std::endl;
	// for(auto& e : vv) std::cout << e << " "; std::cout << std::endl;
}

int main() {
	try {
		throwing_main();
	} catch(const pom::maths::exception& e) {
		std::cerr << "pom::maths::exception: " << e.what() << std::endl;
		return -1;
	} catch(...) {
		std::cerr << "Unhandled exception." << std::endl;
		return -1;
	}
}
