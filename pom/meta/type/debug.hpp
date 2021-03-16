#pragma once

#include "type.hpp"

#include <ostream>

namespace pom {
namespace meta {

template<typename Ty>
std::ostream& operator<<(std::ostream& os, type<Ty>) {
	return os << typeid(Ty).name();
}

}}
