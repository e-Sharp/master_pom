#include "pom/maths/object/interval.hpp"
#include "pom/maths/preset/default/all.hpp"

#include <iostream>

using namespace pom::maths::default_preset;

void throwing_main() {
	constexpr auto i = interval<int>{1, 3};
	std::cout << lower(i) << " " << upper(i) << " " << length(i) << std::endl;
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
