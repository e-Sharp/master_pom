#include <pom/declarative/all.hpp>

#include <pom/meta/type/all.hpp>
#include <pom/meta/type_list/all.hpp>

#include <cmath>
#include <iostream>
#include <tuple>

using namespace pom::decl;
using namespace pom::meta;

struct floor_ {};

template<typename... D, typename Ty>
Ty make(const data<D...>, floor_, Ty val) {
	std::cout << "floor" << std::endl;
	return std::floor(val);
}

struct fract {};

consteval type_list<floor_> dependencies(type<fract>) { return {}; }

template<typename... D, typename Ty>
Ty make(const data<D...>& d, fract, Ty val) {
	std::cout << "fract" << std::endl;
	return val - d.get(type<floor_>());
}

int main() {
	auto data = make_all<fract>(4.5);
	std::cout << data.get(type<fract>()) << std::endl;
}
