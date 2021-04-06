#pragma once

#include "pom/terrain/function/concept/first_order_function.hpp"

#include <type_traits>

namespace pom::terrain {

struct noise {};

template<>
struct is_first_order_function<noise>
: std::true_type {};

}
