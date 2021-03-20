#pragma once

#include "type.hpp"

namespace decl {

template<typename TA, typename TB> consteval
bool same(type<TA>, type<TB>) { return false; }

template<typename T> consteval
bool same(type<T>, type<T>) { return true; }

}
