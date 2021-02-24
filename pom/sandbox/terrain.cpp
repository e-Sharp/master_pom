#include "pom/io_std/all.hpp"
#include "pom/io_format/srtm/all.hpp"
#include "pom/io_format/wavefront/all.hpp"
#include "pom/maths/noise.hpp"
#include "pom/maths/vector/all.hpp"
#include "pom/terrain/all.hpp"

#include <cmath>
#include <iostream>
#include <QImage>
#include <vector>
#include <fstream>

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

constexpr auto f_to_i(float f) {
    return static_cast<int>(255.f * f + 0.5f);
}

template<maths::matrix M>
QImage to_image(const M& m) {
    auto im = QImage(static_cast<int>(col_count(m)), static_cast<int>(row_count(m)), QImage::Format_RGB32);
    for(auto r : maths::row_indexes(m)) {
        for(auto c : maths::col_indexes(m)) {
            auto int_i = static_cast<int>(c);
		    auto int_j = static_cast<int>(r);
            auto col = at(row(m, r), c);
            im.setPixelColor(int_i, int_j, qRgba(f_to_i(at(col, 0)), f_to_i(at(col, 1)), f_to_i(at(col, 2)), 255));
        }
    }
    return im;
}

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

    auto noise_warping_t = warping(perlin_t, [](point p) {
        return noise_warping()(p);
    });

    auto h = [noise_warping_t](float x, float y) { return noise_warping_t({x, y}).value; };

    auto hf = heightfield{};
    hf.domain = {{maths_impl::interval{-16 / 9.f, 16 / 9.f}, maths_impl::interval{-1.f, 1.f}}};
    hf.heights = tesselation(h, hf.domain, 1000);

    auto f = io_std::open_file("mesh.obj", std::ios::out);
    io_format::wavefront::write(f, obj{hf});

    

    {
        using color = decltype(maths_impl::vector<float, 3>());
        auto m = same_size_matrix<color>(hf.heights);
        for(auto r : maths::row_indexes(m)) {
            auto sr = row(hf.heights, r);
            auto dr = row(m, r);
            for(auto i : maths::indexes(sr)) {
                auto h = at(sr, i);
                at(dr, i) = h < 0.f ? color{0.f, 0.f, 1.f} : color{1.f, 0.f, 0.f};
            }
        }
        to_image(m).save("texture.png");
    }
    
    auto grads = gradients(h, hf.domain, 1000);

    {
        using color = decltype(maths_impl::vector<float, 3>());
        auto gtex = same_size_matrix<color>(grads);
        for(auto&& [d, s] : ranges::views::zip(row_major(gtex), row_major(grads))) {
            auto g = s;
            auto l = length(g);
            if(l > 1.f) {
                g = 1.f / l * g;
            }
            g = (g + 1.f) * 0.5f;
            d = {at(g, 0), 0.f, at(g, 1)};
        }
        to_image(gtex).save("grads.png");
    }
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
