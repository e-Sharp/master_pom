#pragma once

namespace pom::maths {

template<typename Ty> constexpr
auto cubic_step(const Ty& min, const Ty& max, const Ty& x) {
	if     (x <= min) return Ty(0);
    else if(x >= max) return Ty(1);
    else {
        auto t = (x - min) / (max - min);
        return t * t * (Ty(3) + t * Ty(-2));
    }
}

}
