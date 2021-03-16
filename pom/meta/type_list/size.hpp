#pragma once

#include "type_list.hpp"

#include <cstdlib>

namespace pom {
namespace meta {

template<typename... TL> consteval
std::size_t size(type_list<TL...> l) {
	return sizeof...(TL);
}

}}
