#pragma once

#include <type_traits>

namespace pom::terrain {

template<typename Ty>
struct is_decorator
: std::false_type {};

template<typename Ty>
concept decorator = is_decorator<Ty>::value;

}
