#pragma once

#include "decl/type/type.hpp"

namespace decl {
namespace detail {

template<typename T> consteval
T what(type<T>);

}}
