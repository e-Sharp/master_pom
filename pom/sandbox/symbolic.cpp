#include "pom/symbolic/operation/derivative.hpp"
#include "pom/symbolic/operation/operators.hpp"
#include "pom/symbolic/operation/value.hpp"

#include <iostream>

using namespace pom::symbolic;

template<typename L, typename R> constexpr
auto f(const L& l, const R& r) {
	return l * r + 1;
}

void throwing_main() {
	constexpr auto s = symbol{derivative{product{variable<0>{}, variable<0>{}}, variable<0>{}}};
	constexpr auto v = value(s, 2);
	std::cout << (float) v << std::endl;
}

int main() {
	try {
		throwing_main();
	} catch(...) {
		std::cerr << "Unhandled exception." << std::endl;
	}
	return 0;
}
