#pragma once

#include "lerp.hpp"

#include "pom/terrain/operator/multiplication/product.hpp"
#include "pom/terrain/operator/scaling/scaling.hpp"
#include "pom/terrain/operator/sum/sum.hpp"
#include "pom/terrain/operator/sum/sum_operation.hpp"
#include "pom/terrain/primitive/constant.hpp"

#include <tuple>

namespace pom::terrain {

template<typename Tuple>
constexpr auto operator|(Tuple&& t, lerp) {
	return sum_operation(
		product(
			get<0>(std::forward<Tuple>(t)),
			get<2>(std::forward<Tuple>(t))),
		product(
			get<1>(std::forward<Tuple>(t)),
			sum_operation(
				product(
					get<2>(std::forward<Tuple>(t)), 
					constant(-1.f)), 
				constant(1.f))));
}

}
