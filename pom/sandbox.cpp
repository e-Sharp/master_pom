#include <cmath>
#include <iostream>

#include "pom/ctree/global_prim.hpp"
#include "pom/ctree/modulation_op.hpp"
#include "pom/ctree/warping_op.hpp"

template<typename Ty>
constexpr auto pi = static_cast<Ty>(3.14159265359L);

template<typename Ty>
auto constant_f(Ty value) {
    return [value](point) {
        return value;
    };
}

auto radial_cos(point p) {
    auto x = 2.f * pi<float> * p[0];
    auto y = 2.f * pi<float> * p[1];
    return std::cos(std::sqrt(x * x + y * y));
}

constexpr
auto wyvill_fall_off_filter(float r) {
    auto rr = r * r;
    return [rr](point p) {
        auto dd = p[0] * p[0] + p[1] * p[1];
        auto p1 = rr - dd;
        return p1 > 0.f ? p1 * p1 * p1 : 0.f;
    };
}

int main() {
    // [-2, 2]^2 100^2
    auto wyvill_t = shared_ctree(new global_prim{
        wyvill_fall_off_filter(1.f),
        [](point) { return 1.f; }
    });

    // [-5, 5]^2 500^2
    auto warped_wyvill_t = shared_ctree(new warping_op{
        [](point p) {
            auto d = distance(p);
            return point{d * p[0], d * p[1]};
        },
        wyvill_t
    });

    // [-5, 5]^2 500^2
    auto squared_warped_wyvill_t = shared_ctree(new modulation_op{
        [](float h) { return h * h; },
        warped_wyvill_t
    });

    std::cout << wyvill_t->eval_at({1, 0}).height << std::endl;
}
