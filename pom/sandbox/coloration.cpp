#include "pom/io_std/all.hpp"
#include "pom/io_format/srtm/all.hpp"
#include "pom/io_format/wavefront/all.hpp"
#include "pom/maths/matrix/interpolation.hpp"
#include "pom/maths/numeric.hpp"
#include "pom/maths/noise.hpp"
#include "pom/maths/vector/all.hpp"
#include "pom/terrain/all.hpp"
#include "pom/terrain/paths.hpp"

#include <cmath>
#include <iostream>
#include <QImage>
#include <vector>
#include <fstream>

using namespace pom;
using namespace pom::maths;
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

//lerp
static_vector<float, 3> lerp(static_vector<float, 3> l, static_vector<float, 3> r, float t) {
    auto x = at(l, 0) + t * at(r, 0) / at(l, 0);
    auto y = at(l, 1) + t * at(r, 1) / at(l, 1);
    auto z = at(l, 2) + t * at(r, 2) / at(l, 2);
    auto vec = maths_impl::vector<3>({x, y, z});
    return vec;
}

static_vector<float, 3> color(static_vector<float, 3> xyz) {
    //////////////////////////////////////////////////////////////////////////////////////////////// PAR ICI
    // auto black = maths_impl::vector<3>({.0F, .0F, .0F});
    // auto white = maths_impl::vector<3>({1.F, 1.0F, 1.0F});
    // auto grey = maths_impl::vector<3>({.59F, .59F, .59F});
    // auto yellow = maths_impl::vector<3>({.89F, .98F, .5F});
    // auto skin = maths_impl::vector<3>({.9F, .75F, .4F});
    // auto green = maths_impl::vector<3>({.153F, .86F, .0F});
    // auto darkgreen = maths_impl::vector<3>({.15F, .45F, .0F});
    // auto blue = maths_impl::vector<3>({.0F, .0F, 1.0F});

    auto darkblue = maths_impl::vector<3>({.0F, .0F, .65F});
    auto darkgreen = maths_impl::vector<3>({.15F, .45F, .0F});
    auto brown = maths_impl::vector<3>({.56F, .46F, .0F});
    auto white = maths_impl::vector<3>({1.F, 1.0F, 1.0F});
    auto grey = maths_impl::vector<3>({.59F, .59F, .59F});

    auto hmax = 8848;
    auto snow = 1000;
    auto rock = 100;
    auto water = 0;


    if(at(xyz, 2) >= snow) {
        float t = (at(xyz, 2) - snow) / (hmax - snow);
        return lerp(grey, white, t);
    }
    else if(at(xyz, 2) >= rock) {
        float t = (at(xyz, 2) + rock) / (snow - rock);
        return lerp(brown, grey, t);
    }
    else {//if(at(xyz, 2) >= -.75) {
        float t = (at(xyz, 2) - water) / (rock - water);
        return lerp(darkblue, brown, t);
    }

    //return xyz / length(xyz);
}

void throwing_main() {
    auto hf = heightfield{};
    { // Reading data.
        auto srtm = maths_impl::matrix<float>();
        { // Reading SRTM.
            auto srtm_file = io_std::open_file(
                "C:/Users/yoanp/Documents/GitHub/master_pom/data/srtmgl3_v003_hgt/n28e083.hgt",
                std::ios::binary | std::ios::in);
            srtm = io_format::srtm::read_srtm3(srtm_file);
            for(auto&& e : row_major(srtm)) e /= 90.f;
        }
        hf.x_domain = hf.y_domain = maths_impl::interval_0_n(1201.f * 90.f / 90.f);
        hf.heights = matrix_cr<float>(3000, 3000);
        for(auto ri : maths::row_indexes(hf.heights)) 
        for(auto ci : maths::col_indexes(hf.heights)) {
            at_cr(hf.heights, ci, ri) = bilerp_normalized_cr(srtm,
                float(ci) / (col_count(hf.heights) - 1),
                float(ri) / (row_count(hf.heights) - 1));
        }
    }
    if(false) { // Outputing mesh.
        auto chunk_side = std::size_t{256};
        auto cmax = positive_ceiled_quotient(col_count(hf.heights), chunk_side);
        auto rmax = positive_ceiled_quotient(row_count(hf.heights), chunk_side);
        
        auto w = wavefront(view_cr(hf.heights, {0, 0}, {1, 1}));

        auto ci_to_x = ci_to_x_mapping(hf);
        auto ri_to_y = ri_to_y_mapping(hf);

        for(std::size_t ri = 0; ri < rmax; ++ri) {
            auto r1 = ri * chunk_side;
            auto r2 = std::min(r1 + chunk_side, row_count(hf.heights) - 1);
            for(std::size_t ci = 0; ci < cmax; ++ci) {
                auto c1 = ci * chunk_side;
                auto c2 = std::min(c1 + chunk_side, col_count(hf.heights) - 1);
                if(c1 != c2 && r1 != r2){
                    auto f = io_std::open_file(std::string(output_folder) + "/mesh_" + std::to_string(ci) + "_" + std::to_string(ri) + ".obj", std::ios::out);
                    w.heights = view_cr(hf.heights, {c1, r1}, {c2 - c1, r2 - r1});
                    w.x_domain = {ci_to_x(c1), ci_to_x(c2)};
                    w.y_domain = {ri_to_y(r1), ri_to_y(r2)};
                    io_format::wavefront::write(f, w);
                }
            }
        }
    }
    { // Outputing normals.
        using normal = maths_impl::static_vector<float, 3>;
        auto ns = maths_impl::same_size_matrix<normal>(hf.heights);
        for(auto ri : maths::row_indexes(ns))
        for(auto ci : maths::col_indexes(ns)) {
            auto g = gradient(
                [&](float x, float y) { return maths::bilerp_cr(hf.heights, x, y); },
                maths_impl::vector<2>({float(ci), float(ri)}), 1.f);
            auto gx = maths_impl::vector<3>({1.f, 0.f, at(g, 0)});
            auto gy = maths_impl::vector<3>({0.f, 1.f, at(g, 1)});
            auto n = cross(gx, gy);
            n = n / length(n);
            at_cr(ns, ci, ri) = n / 2.f + 0.5f;
        }
        to_image(ns).save((std::string(output_folder) + "/normals.png").c_str());
    }
    //{ // Outputing gradients.
    //    auto grads = maths_impl::same_size_matrix<decltype(maths_impl::vector<float, 2>())>(hf.heights);
    //    for(auto ri : maths::row_indexes(grads))
    //    for(auto ci : maths::col_indexes(grads)) {
    //        auto g = at_cr(grads, ci, ri) = gradient(
    //            [&](float x, float y) { return maths::bilerp_cr(hf.heights, x, y); },
    //            maths_impl::vector<2>({float(ci), float(ri)}), 1.f);
    //    }
    //    using color = decltype(maths_impl::vector<float, 3>());
    //    auto gtex = same_size_matrix<color>(grads);
    //    for(auto&& [d, s] : maths::row_major(gtex, grads)) {
    //        auto g = s / 10.f;
    //        auto l = maths::length(g);
    //        if(l > 1.f) {
    //            g = 1.f / l * g;
    //        }
    //        g = (g + 1.f) / 2.f;
    //        d = {at(g, 0), 0.f, at(g, 1)};
    //    }
    //    to_image(gtex).save("gradients.png");
    //}
    { // Outputing texture.
       auto tex = maths_impl::same_size_matrix<static_vector<float, 3>>(hf.heights);
       for(auto ri : maths::row_indexes(hf.heights))
       for(auto ci : maths::col_indexes(hf.heights)) {
           auto x = hf.c_to_x(ci);
           auto y = hf.r_to_y(ri);
           auto z = at_cr(hf.heights, ci, ri);
           at_cr(tex, ci, ri) = color({x, y, z});
       }
       to_image(tex).save("texture.png");
    }
}

int main() {
    try {
        throwing_main();
    } catch(const std::exception& e) {
        std::cerr << "std::exception: " << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Unhandled exception." << std::endl;
        return -1;
    }
    return 0;
}
