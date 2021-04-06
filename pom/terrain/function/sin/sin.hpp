#pragma once

#include "pom/terrain/function/concept/first_order_function.hpp"

#include <type_traits>

namespace pom::terrain {

struct sin {};

template<>
struct is_first_order_function<sin>
: std::true_type {};

}
