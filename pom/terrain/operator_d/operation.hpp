#pragma once

namespace pom::terrain {

template<typename Ty>
struct is_operation {
	static constexpr bool value = false;
};

template<typename Ty>
concept operation = is_operation<Ty>::value;

}
