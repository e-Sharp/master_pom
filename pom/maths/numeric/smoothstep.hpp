#pragma once

namespace pom {
namespace maths {

template<typename Ty> constexpr
auto smoothstep1(const Ty& min, const Ty& max, const Ty& x) {
    if(x <= min)      return Ty(0);
    else if(x >= max) return Ty(1);
    else {
        auto nx = (x - min) / (max - min);
        return nx * nx * (3 - nx * 2);
    }
}

}}
