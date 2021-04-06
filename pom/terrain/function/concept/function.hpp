#pragma once

#include "first_order_function.hpp"
#include "higher_order_function.hpp"

namespace pom::terrain {

template<typename Ty>
concept function
= (first_order_function<Ty> || higher_order_function<Ty>);

}
