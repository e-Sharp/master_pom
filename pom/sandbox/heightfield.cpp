#include "pom/maths/object/interval.hpp"
#include "pom/maths/preset/default/all.hpp"
#include "pom/terrain/tesselation.hpp"

#include <iostream>

using namespace pom::maths::default_preset;
using namespace pom::terrain;

void throwing_main() {
	auto d = domain{{interval<float>{1, 10}, interval<float>{1, 10}}};
	auto m = tesselation(
		[](float x, float y) { return x + y; }, d, 10);
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
