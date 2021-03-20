#pragma once

#include "type_list.hpp"

namespace decl {

template<typename... TL> consteval
bool empty(type_list<TL...>) { return false; }

consteval
bool empty(type_list<>) { return true; }

}
