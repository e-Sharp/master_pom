#pragma once

#include "type.hpp"

namespace pom {
namespace meta {

template<typename Ta, typename Tb> consteval
bool same(type<Ta>, type<Tb>) { return false; }

template<typename Ty> consteval
bool same(type<Ty>, type<Ty>) { return true; }

}}
