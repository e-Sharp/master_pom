#include "pom/io_qt/all.hpp"
#include "pom/io_std/all.hpp"
#include "pom/io_format/srtm/all.hpp"
#include "pom/io_format/wavefront/all.hpp"
#include "pom/maths/matrix/interpolation.hpp"
#include "pom/maths/vector/all.hpp"
#include "pom/maths/gradient.hpp"
#include "pom/maths/noise.hpp"
#include "pom/maths/numeric.hpp"
#include "pom/terrain/all.hpp"
#include "pom/terrain/examples.hpp"
#include "pom/terrain/imports.hpp"
#include "pom/terrain/paths.hpp"
#include "pom/terrain/terrain_test.hpp"

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>

using namespace pom;
using namespace pom::maths;
using namespace pom::maths;
using namespace pom::terrain;

template<typename Ty>
constexpr auto pi = static_cast<Ty>(3.14159265359L);

//lerp
static_vector<float, 3> lerp(static_vector<float, 3> l, static_vector<float, 3> r, float t) {
    auto x = at(l, 0) * (1 - t) + at(r, 0) * t;
    auto y = at(l, 1) * (1 - t) + at(r, 1) * t;
    auto z = at(l, 2) * (1 - t) + at(r, 2) * t;

    auto vec = maths::vector<3>({x, y, z});
    return vec;
}

float randMap() {
    float min = 0;
    float max = 1;
    return min + (float)(rand()) / ((float)(RAND_MAX / (max - min)));
}

// void sandTexture() {
//     auto white = maths_impl::vector<3>({1.F, 1.0F, 1.0F});
//     const int size = 1024;
//     float xPeriod = 5;
//     float yPeriod = 10;
//     std::vector<float> tex(size);
//     for(auto i = 0; i < size; ++i) {
//         for(auto j = 0; j < size; ++j) {
//             float xy = i * xPeriod + j * yPeriod; 
//             tex[size * j + i] = randMap() * white * sin(xy * pi<float> / 10);
//         }
//     }
// }

static_vector<float, 3> color(static_vector<float, 3> xyz, float slope) {
    //////////////////////////////////////////////////////////////////////////////////////////////// PAR ICI
    // auto hmax = 10000;
    // auto ground = 0;
    // auto snow = 2000;
    // auto rock = 3000;
    // auto grass = 1500;

    // auto elevation = at(xyz, 2);

    auto black = maths_impl::vector<3>({.0F, .0F, .0F});
    auto white = maths_impl::vector<3>({1.F, 1.0F, 1.0F});
    auto grey = maths_impl::vector<3>({.41F, .41F, .41F});

    //Grayscale slope
    return lerp(black, white, slope);

    // Grayscale height
    // if(elevation > ground) {
    //     float t = (elevation - ground) / (hmax - ground);
    //     return lerp(black, white, t);
    // }

    //Snow
    // if(slope < 0.35) {
    //     auto blendAmount = slope / 0.35;
    //     return lerp(grey, white, blendAmount);
    // }
    // else if(slope >= 0.35) {
    //     auto t = (elevation - ground) / (hmax - ground);
    //     return lerp(grey, black, t);
    // }

    //Snow and grass
    //snow = 2000
    //grass = 1500
    // auto darkgreen = maths_impl::vector<3>({.49F, .55F, .3F});
    // auto green = maths_impl::vector<3>({.71F, .73F, .38F});
    // auto darkbrown = maths_impl::vector<3>({.22F, .16F, .11F});
    // auto brown = maths_impl::vector<3>({.45F, .33F, .16F});
    // auto beige = maths_impl::vector<3>({.9F, .85F, .76F});
    // auto skyblue = maths_impl::vector<3>({.71F, .89F, .86F});

    // if(elevation > ground) {
    //     if(slope < 0.35 && elevation > snow) {
    //         auto blendAmount = slope / 0.35;
    //         return lerp(grey, white, blendAmount);
    //     }
    //     else if(slope < 0.3 && elevation < grass) {
    //         auto blendAmount = slope / 0.3;
    //         return lerp(darkgreen, green, blendAmount);
    //     }
    //     else
    //         return lerp(darkbrown, grey, slope);
    // }

    //desert


    //sand texture test
    // float xPeriod = 5;
    // float yPeriod = 10;

    // auto x = at(xyz, 0);
    // auto y = at(xyz, 1);

    // float xy = x * xPeriod + y * yPeriod; 
    // return randMap() * white * sin(xy * pi<float> / 10);
}

vec3f color(const himalayas& hs, vec2f xy) {
    auto h = height(hs, xy);
    auto g = gradient(hs, xy);
    auto n = normal(hs, xy);
    //float slope = 1 - at(n, 2);
    float slope = atan(sqrt(at(n, 0) * at(n, 0) + at(n, 1) * at(n, 1)) / at(n, 2));
    slope = (slope / (pi<float> / 2));
    return color({at(xy, 0), at(xy, 1), h}, slope);
}

void throwing_main() {
    auto h = dune();
    auto hf = heightfield{};
    { // Reading data.
        hf.heights = matrix_cr<float>(1000, 1000);

        hf.x_domain = h.x_domain;
        auto ci_to_x = maths::mapping(maths::interval_0_n(col_count(hf.heights)), hf.x_domain);
        hf.y_domain = h.y_domain;
        auto ri_to_y = maths::mapping(maths::interval_0_n(row_count(hf.heights)), hf.y_domain);

        for(auto ri : maths::row_indexes(hf.heights)) {
            auto y = ri_to_y(ri);
            for(auto ci : maths::col_indexes(hf.heights)) {
                auto x = ci_to_x(ci);
                at_cr(hf.heights, ci, ri) = height({x, y});
            }
        }
    }
    { // Outputing mesh.
        auto chunk_side = std::size_t{512};
        auto cmax = positive_ceiled_quotient(col_count(hf.heights), chunk_side);
        auto rmax = positive_ceiled_quotient(row_count(hf.heights), chunk_side);
        
        auto w = wavefront(view_cr(hf.heights, {0, 0}, {1, 1}));

        auto ci_to_x = ci_to_x_mapping(hf);
        auto ri_to_y = ri_to_y_mapping(hf);
        auto ci_to_u = ci_to_u_mapping(hf);
        auto ri_to_v = ri_to_v_mapping(hf);

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
                    w.u_domain = {ci_to_u(c1), ci_to_u(c2)};
                    w.v_domain = {ri_to_v(r1), ri_to_v(r2)};
                    io_format::wavefront::write(f, w);
                }
            }
        }
    }
    { // Outputing normals.
        auto ns = maths::same_size_matrix<vec3f>(hf.heights);

        auto ci_to_x = maths::mapping(maths::interval_0_n(col_count(ns) - 1), h.x_domain);
        auto ri_to_y = maths::mapping(maths::interval_0_n(row_count(ns) - 1), h.y_domain);

        for(auto ri : maths::row_indexes(ns))
        for(auto ci : maths::col_indexes(ns)) {
            auto n = normal(h, {ci_to_x(ci), ri_to_y(ri)})  / 2.f + 0.5f;
            at_cr(ns, ci, ri) = n;
        }
        io_qt::to_image(ns).save((std::string(output_folder) + "/normals.png").c_str());
    }
    { // Outputing texture.
        auto tx = maths::same_size_matrix<static_vector<float, 3>>(hf.heights);
        auto ci_to_x = ci_to_x_mapping(hf);
        auto ri_to_y = ri_to_y_mapping(hf);
        for(auto ri : maths::row_indexes(hf.heights))
        for(auto ci : maths::col_indexes(hf.heights)) {
            auto x = ci_to_x(ci);
            auto y = ri_to_y(ri);
            auto z = at_cr(hf.heights, ci, ri);
            at_cr(tx, ci, ri) = color(h, {x, y});
            //at_cr(tx, ci, ri) = color({x, y, z});
        }
        io_qt::to_image(tx).save((std::string(output_folder) + "/texture.png").c_str());
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
