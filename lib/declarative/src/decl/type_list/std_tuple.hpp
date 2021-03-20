#pragma once

#include "type_list.hpp"

#include <tuple>

namespace decl {

template<typename... TL> constexpr
std::tuple<TL...> std_tuple_of(type_list<TL...>) { return {}; }

}
