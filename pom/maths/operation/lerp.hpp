#pragma once

namespace pom::maths {

template<typename Ty, typename Scalar> constexpr
auto lerp(const Ty& a, const Ty& b, const Scalar& t) {
	return (Scalar(1) - t) * a + t * b;
}

}
