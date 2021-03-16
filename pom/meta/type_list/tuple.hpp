#pragma once

#include "type_list.hpp"

#include <tuple>

namespace pom {
namespace meta {

template<typename... TL> constexpr
std::tuple<TL...> tuple_of(type_list<TL...>) { return {}; }

}}
