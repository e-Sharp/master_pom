#pragma once

#include "type.hpp"

namespace decl {
namespace detail {

template<typename Ty> consteval
type<Ty> type_of(Ty) { return {}; }

}}
