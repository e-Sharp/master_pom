#pragma once

#include "pom/terrain/operator/operation.hpp"

#include <type_traits>

namespace pom::terrain {

struct multiplication {};

template<>
struct is_operation<multiplication> : std::true_type {};

}
