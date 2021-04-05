#pragma once

namespace pom::maths {

template<typename Ty> constexpr
Ty clamp(const Ty& x, const Ty& min, const Ty& max) {
	if(x <= min) {
		return min;
	} else if(x >= max) {
		return max;
	} else {
		return x;
	}
}

}
