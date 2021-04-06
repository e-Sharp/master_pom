#pragma once

#include <type_traits>

namespace pom::terrain {

template<typename Default>
struct is_higher_order_function : std::false_type {};

template<typename Ty>
concept higher_order_function
= is_higher_order_function<Ty>::value;

}
