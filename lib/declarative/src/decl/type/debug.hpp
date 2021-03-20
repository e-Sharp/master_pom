#pragma once

#include "type.hpp"

#include <ostream>

namespace decl {

template<typename Ty>
std::ostream& operator<<(std::ostream& os, type<Ty>) {
	return os << typeid(Ty).name();
}

}
