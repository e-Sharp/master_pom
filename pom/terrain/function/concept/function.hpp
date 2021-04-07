#pragma once

#include "first_order_function.hpp"
#include "higher_order_function.hpp"

namespace pom::terrain {

template<typename Ty>
struct is_function {
	static constexpr bool value 
	= is_first_order_function<Ty>::value
	|| is_higher_order_function<Ty>::value;
};

template<typename Ty>
concept function = is_function<Ty>::value;

}
