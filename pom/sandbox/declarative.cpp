#include <pom/declarative/all.hpp>
#include <pom/meta/type/all.hpp>
#include <pom/meta/type_list/all.hpp>

#include <iostream>
#include <tuple>

using namespace pom::decl;
using namespace pom::meta;


struct b {};
struct c {};
struct d {};
struct e {};

struct a {};

consteval type_list<c, d> dependencies(type<a>) { return {}; }

template<typename... D>
a make(const data<D...> d, a) {
	std::cout << "a" << std::endl;
	return {};
}

consteval type_list<d> dependencies(type<b>) { return {}; }

template<typename... D>
int make(const data<D...>& d, b) {
	std::cout << "b" << std::endl;
	return {};
}

consteval type_list<e> dependencies(type<c>) { return {}; }

template<typename... D>
c make(const data<D...> d, c) {
	std::cout << "c" << std::endl;
	return {};
}

template<typename... D>
d make(const data<D...> da, d) {
	std::cout << "d" << std::endl;
	return {};
}

template<typename... D>
e make(const data<D...> d, e) {
	std::cout << "e" << std::endl;
	return {};
}

int main() {
	make_all<b>();
}
