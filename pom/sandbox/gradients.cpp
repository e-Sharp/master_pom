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
using namespace pom::maths_impl;
using namespace pom::terrain;

static_vector<float, 3> color(static_vector<float, 3> xyz) {
    //////////////////////////////////////////////////////////////////////////////////////////////// PAR ICI
    return xyz / length(xyz);
}

template<maths::interval I, typename Ty> constexpr
auto sub(I i, Ty ith, Ty n) {
    auto l = lower(i) + ith * length(i) / n;
    auto u = lower(i) + (ith + 1) * length(i) / n;
    return I(l, u);
}

void throwing_main() {
    auto h = himalayas();
    auto hf = heightfield{};
    { // Reading data.
        hf.heights = matrix_cr<float>(8000, 8000);

        hf.x_domain = h.x_domain;
        auto ci_to_x = maths::mapping(maths_impl::interval_0_n(col_count(hf.heights)), hf.x_domain);
        hf.y_domain = h.y_domain;
        auto ri_to_y = maths::mapping(maths_impl::interval_0_n(row_count(hf.heights)), hf.y_domain);

        for(auto ri : maths::row_indexes(hf.heights)) {
            auto y = ri_to_y(ri);
            for(auto ci : maths::col_indexes(hf.heights)) {
                auto x = ci_to_x(ci);
                at_cr(hf.heights, ci, ri) = height(h, {x, y});
            }
        }
        
        auto erosion = [](vec3f normal) {
            auto xy = vec2f({at(normal, 0), at(normal, 1)});
            auto l = length(xy);
            auto n = 0.f;
            if(l != 0) {
                n = fbm([](vec2f xy) { return perlin(xy / 8.f); }, 4, (l + 10.f) / l * xy);
            }
            return 300.f * lerp(0.f, n, smoothstep_1_((l - 0.1f) / (1.f - .1f)));
        };

        for(auto ri : row_indexes(hf.heights)) {
            auto y = ri_to_y(ri);
            for(auto ci : col_indexes(hf.heights)) {
                auto x = ci_to_x(ci);
                at_cr(hf.heights, ci, ri) = at_cr(hf.heights, ci, ri) /*+ erosion(normal(h, {x, y}))*/;
            }
        }
    }
    { // Outputing mesh.
        auto chunk_side = std::size_t{512};
        auto cmax = 2; //positive_ceiled_quotient(col_count(hf.heights), chunk_side);
        auto rmax = 2; //positive_ceiled_quotient(row_count(hf.heights), chunk_side);
        
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
        auto ns = maths_impl::same_size_matrix<vec3f>(hf.heights);

        auto ci_to_x = maths::mapping(maths_impl::interval_0_n(col_count(ns) - 1), h.x_domain);
        auto ri_to_y = maths::mapping(maths_impl::interval_0_n(row_count(ns) - 1), h.y_domain);

        for(auto ri : maths::row_indexes(ns))
        for(auto ci : maths::col_indexes(ns)) {
            auto n = normal(h, {ci_to_x(ci), ri_to_y(ri)})  / 2.f + 0.5f;
            at_cr(ns, ci, ri) = n;
        }
        io_qt::to_image(ns).save((std::string(output_folder) + "/normals.png").c_str());
    }
    { // Outputing texture.
        auto tx = maths_impl::same_size_matrix<static_vector<float, 3>>(hf.heights);
        auto ci_to_x = ci_to_x_mapping(hf);
        auto ri_to_y = ri_to_y_mapping(hf);
        for(auto ri : maths::row_indexes(hf.heights))
        for(auto ci : maths::col_indexes(hf.heights)) {
            auto x = ci_to_x(ci);
            auto y = ri_to_y(ri);
            at_cr(tx, ci, ri) = color(h, {x, y});
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
