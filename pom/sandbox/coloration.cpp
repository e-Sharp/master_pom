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

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

using namespace pom;
using namespace pom::maths;
using namespace pom::maths;
using namespace pom::terrain;

//lerp
static_vector<float, 3> lerp(static_vector<float, 3> l, static_vector<float, 3> r, float t) {
    auto x = at(l, 0) * (1 - t) + at(r, 0) * t;
    auto y = at(l, 1) * (1 - t) + at(r, 1) * t;
    auto z = at(l, 2) * (1 - t) + at(r, 2) * t;

    auto vec = maths::vector<3>({x, y, z});
    return vec;
}

static_vector<float, 3> color(static_vector<float, 3> xyz, float slope) {
    //////////////////////////////////////////////////////////////////////////////////////////////// PAR ICI
    auto black = maths::vector<3>({.0F, .0F, .0F});
    auto yellow = maths::vector<3>({.89F, .98F, .5F});
    auto skin = maths::vector<3>({.9F, .75F, .4F});
    auto green = maths::vector<3>({.153F, .86F, .0F});
    auto blue = maths::vector<3>({.0F, .0F, 1.0F});
    auto darkblue = maths::vector<3>({.01F, .13F, .67F});
    auto darkgreen = maths::vector<3>({.15F, .48F, .0F});
    auto brown = maths::vector<3>({.38F, .24F, .01F});
    auto darkbrown = maths::vector<3>({.313F, .03F, .07F});
    auto white = maths::vector<3>({1.F, 1.0F, 1.0F});
    auto grey = maths::vector<3>({.41F, .41F, .41F});
    auto br = maths::vector<3>({.4F, .13F, .05F});
    auto orange = maths::vector<3>({.98F, .71F, .25F});
    auto aqua = maths::vector<3>({.015F, .54F, .58F});

    auto hmax = 10000;
    auto hmin = 0;
    auto snow = 6500;
    auto rock = 3500;
    auto grass = 1000;
    auto beach = 500;
    auto water = 0;

    auto elevation = at(xyz, 2);

    // Snow
    // if(elevation >= snow) {
    //     float t = (elevation - snow) / (hmax - snow);
    //     return white;
    // }
    // else if(elevation >= rock) {
    //     float t = (elevation - rock) / (snow - rock);
    //     if(slope < 0.1) {
    //         return white;
    //     }
    //     else if(0.1 < slope < 0.7) {
    //         return lerp(grey, white, t);
    //     }
    //     else {
    //         return lerp(black, grey, t);
    //     }
    // }
    // else {
    //     float t = (elevation - hmin) / (rock - hmin);
    //     if(slope < 0.05) {
    //         return white;
    //     }
    //     else if(0.05 < slope < 0.7) {
    //         return lerp(brown, white, t);
    //     }
    //     else {
    //         return lerp(brown, grey, t);
    //     }
    // }

    //Grass mountains
    // if(elevation >= snow) {
    //     float t = (elevation - snow) / (hmax - snow);
    //     return lerp(green, brown, t);
    // }
    // else if(elevation >= rock) {
    //     float t = (elevation - rock) / (snow - rock);
    //     if(slope < 0.01) {
    //         return darkgreen;
    //     }
    //     else if(0.2 < slope < 0.7) {
    //         return lerp(darkgreen, brown, t);
    //     }
    //     else {
    //         return lerp(darkbrown, brown, t);
    //     }
    // }
    // else {
    //     float t = (elevation - hmin) / (snow - hmin);
    //     if(slope < 0.2) {
    //         return lerp(darkgreen, green, t);
    //     }
    //     else if(0.2 < slope < 0.7) {
    //         return lerp(darkgreen, brown, t);
    //     }
    //     else {
    //         return lerp(brown, grey, t);
    //     }
    // }

    //desert
    if(elevation >= snow) {
        float t = (elevation - snow) / (hmax - snow);
        return lerp(darkbrown, br, t);
    }
    else if(elevation >= rock) {
        float t = (elevation - rock) / (snow - rock);
        if(slope < .05) {
            return skin;
        }
        else if(.05 < slope < .7) {
            return lerp(skin, brown, t);
        }
        else
            return lerp(brown, darkbrown, t);
    }
    else if(elevation >= grass) {
        float t = (elevation - grass) / (rock - grass);
        if(slope <= 0) {
            return lerp(darkblue, blue, t);
        }
        else if(.05 < slope < .7) {
            return lerp(brown, skin, t);
        }
        else
            return lerp(orange, brown, t);
    }
    else if(elevation >= beach) {
        float t = (elevation - beach) / (grass - beach);
        if(slope < .001)
            return lerp(blue, aqua, t);
        else
            return lerp(yellow, orange, t);
    }
    else {
        float t = (elevation - water) / (beach - water);
        return lerp(blue, aqua, t);
    }
}

vec3f color(const himalayas& hs, vec2f xy) {
    auto h = height(hs, xy);
    auto g = gradient(hs, xy);
    auto n = normal(hs, xy);
    float slope = 1 - at(n, 2);
    return color({at(xy, 0), at(xy, 1), h}, slope);
}

void throwing_main() {
    auto h = himalayas();
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
                at_cr(hf.heights, ci, ri) = height(h, {x, y});
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
