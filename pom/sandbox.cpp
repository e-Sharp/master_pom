#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

#include "pom/io/std/all.hpp"
#include "pom/io/wavefront/all.hpp"
#include "pom/maths/function/noise.hpp"
#include "pom/maths/function/vector/all.hpp"
#include "pom/terrain/all.hpp"

using namespace pom;
using namespace pom::maths::default_preset;
using namespace pom::terrain;

using pom::dynamic_matrix;
using pom::col;
using pom::row;

template<typename Ty>
constexpr auto pi = static_cast<Ty>(3.14159265359L);

template<typename Ty>
auto constant_f(Ty value) {
    return [value](point) {
        return value;
    };
}

auto radial_cos(point p) {
    auto x = 2.f * pi<float> * at(p, 0);
    auto y = 2.f * pi<float> * at(p, 1);
    return std::cos(std::sqrt(x * x + y * y));
}

constexpr
auto wyvill_fall_off_filter(float r) {
    auto rr = r * r;
    return [rr](point p) {
        auto dd = dot(p, p);
        auto p1 = rr - dd;
        return p1 > 0.f ? p1 * p1 * p1 : 0.f;
    };
}

constexpr
auto wyvill_fall_off_filter(point c, float r) {
    auto rr = r * r;
    return [c, rr](point p) {
        auto dd = (at(p, 0) - at(c, 0)) * (at(p, 0) - at(c, 0)) + (at(p, 1) - at(c, 1)) * (at(p, 1) - at(c, 1));
        //auto dd = dot(c, p);
        auto p1 = rr - dd;
        return p1 > 0.f ? p1 * p1 * p1 : 0.f;
    };
}


float influence(float d) {
    auto rotation = 5.f;
    d = d > 1 ? 1.f : d;
    auto p = d * (-3 + d * (3 - d)) + 1;
    return rotation * p;
}

constexpr
auto spiral_warping(float r) {
    auto rr = r * r;
    return[rr](point p) {
        //cart to polar
        auto dd = at(p, 0) * at(p, 0) + at(p, 1) * at(p, 1);
        auto d = sqrt(dd);
        auto angle = atan2(at(p,1), at(p, 0));
        auto influ = influence(sqrt(dd / rr));
        angle += influ;
        //polar to cart
        at(p, 0) = d * cos(angle);
        at(p, 1) = d * sin(angle);
        return p;
    };
}

constexpr
auto zoom_warping(float r) {
    auto rr = r * r;
    return[rr](point p) {
        auto z = 3.f / 8.f;
        //cart to polar
        auto dd = at(p, 0) * at(p, 0) + at(p, 1) * at(p, 1);
        auto d = sqrt(dd);
        auto angle = atan2(at(p,1), at(p, 0));

        auto p1 = rr - dd;
        auto e = z + d * d * ((3 - 3 * z) + d * (-2 + 2 * z));
        auto influence = p1 > 0.f ? e : 1.f; 
        d *= influence;
        //polar to cart
        at(p, 0) = d * cos(angle);
        at(p, 1) = d * sin(angle);
        return p;
    };
}

int main() {
    auto perlin_t = [](point p) {
        return eval{
            .value = fbm([](point p) { return perlin(p); }, 5, p),
            .weight = wyvill_fall_off_filter(point{{0, 0}}, 1.f)(p)};
    };

    auto weighted_perlin_t = modulation(perlin_t, [](eval e) {
        e.value *= e.weight;
        return e;
    });

    //auto warped_perlin_t = warping(perlin_t, spiral_warping(point{{0, 0}}, 2.f));
    auto warped_perlin_t = warping(perlin_t, [](point p) {
        return zoom_warping(1)(p - point{{0, 0}});
    });

    auto hf = heightfield{};
    hf.domain = {{interval<float>{-2, 2}, interval<float>{-2, 2}}};
    hf.heights = tesselation(
        [warped_perlin_t](float x, float y) { return warped_perlin_t({{x, y}}).value; },
        hf.domain, 500);

    auto f = io::open_file("warped_perlin_t.obj", std::ios::out);
    io::wavefront::write(f, hf);
}
