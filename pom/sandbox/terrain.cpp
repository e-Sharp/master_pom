#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

#include "pom/io_std/all.hpp"
#include "pom/io/format/wavefront/all.hpp"
#include "pom/maths/noise.hpp"
#include "pom/maths/vector/all.hpp"
#include "pom/terrain/all.hpp"

using namespace pom;
using namespace pom::maths;
using namespace pom::maths_impl;
using namespace pom::terrain;

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

constexpr
auto noise_warping() {
    return[](point p) {
        point polar = {{perlin(p) * 2 * pi<float>, .5f}};
        point cart = {{at(polar, 1) * cos(at(polar, 0)), at(polar, 1) * sin(at(polar, 0))}};
        return p + cart;
    };
}

//

struct heightfield_to_obj {
    struct v {
        maths_impl::static_vector_<float, 3> coords = {};
    };

    struct f {
        maths_impl::static_vector_<std::size_t, 3> indexes = {};
    };

    const heightfield& hf;
};

//

auto f(const heightfield_to_obj&, std::size_t) {
    return heightfield_to_obj::f{};
}

auto f_count(const heightfield_to_obj& hto) {
    auto s = size(hto.hf.heights);
    return 2 * (at(s, 0) - 1) * (at(s, 1) - 1); 
}

auto v(const heightfield_to_obj&, std::size_t) {
    return heightfield_to_obj::v{};
}

auto v_count(const heightfield_to_obj& hto) {
    auto s = size(hto.hf.heights);
    return at(s, 0) * at(s, 1); 
}

//

constexpr std::size_t count(heightfield_to_obj::f) noexcept {
    return 3;
}

auto v(const heightfield_to_obj::f& f, std::size_t i) {
    return at(f.indexes, i);
}

//

auto x(const heightfield_to_obj::v& v) noexcept {
    return at(v.coords, 0);
}

auto y(const heightfield_to_obj::v& v) noexcept {
    return at(v.coords, 1);
}

auto z(const heightfield_to_obj::v& v) noexcept {
    return at(v.coords, 2);
}

//

void throwing_main() {
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
    hf.domain = {{interval_{-2.f, 2.f}, interval_{-2.f, 2.f}}};
    hf.heights = tesselation(
        [weighted_perlin_t](float x, float y) { return weighted_perlin_t({{x, y}}).value; },
        hf.domain, 200);

    auto noise_warping_t = warping(perlin_t, [](point p) {
        return noise_warping()(p);
    });

    {
        auto f = io_std::open_file("test1.obj", std::ios::out);
        io::wavefront_format::write2(f, hf);
    } 
    {
        auto f = io_std::open_file("test2.obj", std::ios::out);
        io::wavefront_format::write(f, heightfield_to_obj{hf});
    }

    // auto f = io_std::open_file("weighted_perlin_t.obj", std::ios::out);
    // io::wavefront_format::write(f, hf);
    // io::wavefront_format::write(f, heightfield_to_obj{hf});
}

int main() {
    try {
        throwing_main();
    } catch(...) {
        std::cerr << "Unhandled exception." << std::endl;
        return -1;
    }
    return 0;
}
