#pragma once

#include "decorator.hpp"

namespace pom::terrain {

template<typename Ty>
struct is_higher_order_function {
	static constexpr bool value = is_decorator<Ty>::value;
};

template<typename Ty>
concept higher_order_function
= is_higher_order_function<Ty>::value;

}
