#pragma once

#include "pom/terrain/operator/operation.hpp"

#include <type_traits>

namespace pom::terrain {

struct lerp {};

template<>
struct is_operation<lerp> : std::true_type {};

}
