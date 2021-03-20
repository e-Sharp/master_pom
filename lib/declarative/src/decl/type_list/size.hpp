#pragma once

#include "type_list.hpp"

#include <cstdlib>

namespace decl {

template<typename... TL> consteval
std::size_t size(type_list<TL...>) {
	return sizeof...(TL);
}

}
