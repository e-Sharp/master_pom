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

constexpr
auto spiral_warping(point c, float r, float rotation) {
    auto rr = r * r;
    return[c, rr, rotation](point p) {
        auto dd = (at(p, 0) - at(c, 0)) * (at(p, 0) - at(c, 0)) + (at(p, 1) - at(c, 1)) * (at(p, 1) - at(c, 1));
        if(dd < rr) {
            //cart to polar
            auto d = sqrt(at(p, 0) * at(p, 0) + at(p, 1) * at(p,1));
            auto a = atan2(at(p,1), at(p, 0));

            auto p1 = rr - dd;
            auto influence =  p1 > 0.f ? p1 * p1 * p1 : 0.f;
            //angle pour willy
            auto angle = a + rotation * influence;

            //polar to cart
            at(p, 0) = d * cos(angle);
            at(p, 1) = d * sin(angle);
        }
    };
}

constexpr
auto noise_warping() {
    return[](point p) {
        point polar = {{perlin(p) * 2 * pi<float>, .5f}};
        point cart = {{at(polar, 1) * cos(at(polar, 0)), at(polar, 1) * sin(at(polar, 0))}};
        return p + cart;
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

    auto hf = heightfield{};
    hf.domain = {{interval<float>{-2, 2}, interval<float>{-2, 2}}};
    hf.heights = tesselation(
        [weighted_perlin_t](float x, float y) { return weighted_perlin_t({{x, y}}).value; },
        hf.domain, 2);

    auto noise_warping_t = warping(perlin_t, [](point p) {
        return noise_warping()(p);
    });

    //tesselation(noise_warping_t, -2, 2, 1000, "noise_warping_t");
    auto f = io::open_file("weighted_perlin_t.obj", std::ios::out);
    io::wavefront::write(f, hf);
}
