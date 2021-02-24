#include "pom/io_std/all.hpp"
#include "pom/io_format/srtm/all.hpp"
#include "pom/io_format/wavefront/all.hpp"
#include "pom/maths/matrix/interpolation.hpp"
#include "pom/maths/noise.hpp"
#include "pom/maths/vector/all.hpp"
#include "pom/terrain/all.hpp"

#include <cmath>
#include <iostream>
#include <QImage>
#include <vector>
#include <fstream>

using namespace pom;
using namespace maths;
using namespace pom::maths_impl;
using namespace pom::terrain;

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

template<typename F2, maths::vector V>
auto gradient(F2 f, V pos, float e) {
    auto x = at(pos, 0);
    auto y = at(pos, 1);
	auto dx = (f(x + e, y    ) - f(x - e, y    )) / (2.f * e);
	auto dy = (f(x    , y + e) - f(x    , y - e)) / (2.f * e);
    auto g = maths_impl::vector<2>({dx, dy});
    return maths_impl::vector<2>({dx, dy});
}

static_vector<float, 3> color(static_vector<float, 3> xyz) {
    //////////////////////////////////////////////////////////////////////////////////////////////// PAR ICI
    return xyz / length(xyz);
}

void throwing_main() {
    auto shf = heightfield{};
    { // Reading SRTM.
        shf.domain = maths_impl::vector<2>({
            maths_impl::interval_0_n(1201.f * 90.f),
            maths_impl::interval_0_n(1201.f * 90.f)});
        auto srtm = io_std::open_file(
            "D:/project/master_pom/data/srtmgl3_v003_hgt/N28E083.hgt",
            std::ios::binary | std::ios::in);
        shf.heights = io_format::srtm::read_srtm3(srtm);
    }
    { // Outputing mesh.
        auto f = io_std::open_file("mesh.obj", std::ios::out);
        io_format::wavefront::write(f, obj{shf});
    }
    { // Outputing gradients.
        auto grads = maths_impl::same_size_matrix<decltype(maths_impl::vector<float, 2>())>(shf.heights);
        for(auto ri : maths::row_indexes(grads))
        for(auto ci : maths::col_indexes(grads)) {
            auto g = at(grads, row(ri), col(ci)) = gradient(
                [&](float x, float y) { return maths::bilerp(shf.heights, maths::col_i<float>(x), maths::row_i<float>(y)); },
                maths_impl::vector<2>({float(ci), float(ri)}), 1.f);
            // std::cout << at(g, 0) << " " << at(g, 1) << std::endl;
        }
        using color = decltype(maths_impl::vector<float, 3>());
        auto gtex = same_size_matrix<color>(grads);
        for(auto&& [d, s] : ranges::views::zip(row_major(gtex), row_major(grads))) {
            auto g = s;
            auto l = maths::length(g);
            if(l > 1.f) {
                g = 1.f / l * g;
            }
            g = (g + 1.f) * 0.5f;
            d = {at(g, 0), 0.f, at(g, 1)};
        }
        to_image(gtex).save("gradients.png");
    }
    { // Outputing texture.
        auto tex = maths_impl::same_size_matrix<static_vector<float, 3>>(shf.heights);
        auto ci_to_x = col_to_x_mapping(shf);
        auto ri_to_y = row_to_y_mapping(shf);
        for(auto ri : maths::row_indexes(shf.heights))
        for(auto ci : maths::col_indexes(shf.heights)) {
            auto x = ci_to_x(ci);
            auto y = ri_to_y(ri);
            auto z = at(shf.heights, maths::col_i(ci), maths::row_i(ri));
            at(tex, maths::col_i(ci), maths::row_i(ri)) = color({x, y, z});
        }
        to_image(tex).save("texture.png");
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
