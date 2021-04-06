#pragma once

#include <type_traits>

namespace pom::terrain {

template<typename Default>
struct is_first_order_function : std::false_type {};

template<typename Ty>
concept first_order_function
= is_first_order_function<Ty>::value;

}
