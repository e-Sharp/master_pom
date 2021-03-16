#pragma once

#include "type_list.hpp"

namespace pom {
namespace meta {

template<typename... Ts> consteval
bool empty(type_list<Ts...>) { return false; }

consteval
bool empty(type_list<>) { return true; }

}}
