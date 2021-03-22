#include "pom/io_format/wavefront/all.hpp"
#include "pom/io_qt/all.hpp"
#include "pom/io_std/all.hpp"
#include "pom/maths/constants.hpp"
#include "pom/maths/interval/all.hpp"
#include "pom/maths_impl/all.hpp"
#include "pom/terrain/all.hpp"

#include <pom/maths_impl/noise/perlin.hpp>
#include <pom/terrain/effect/orange_peel.hpp>
#include <pom/terrain/noise/worley.hpp>
#include <pom/terrain/primitive/torus.hpp>
#include <pom/terrain/test/snowy_sphere.hpp>

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace pom;

void throwing_main() {
    auto ter = terrain::sphere();

    auto resolution = maths_impl::vector<2, std::size_t>({500, 500});
    auto xd = maths_impl::interval<float>(-1.1f, 1.1f);
    auto yd = maths_impl::interval<float>(-1.1f, 1.1f);

    auto heights = maths_impl::matrix_cr<float>(at(resolution, 0), at(resolution, 1));
    auto normals = maths_impl::matrix_cr<terrain::vec3f>(at(resolution, 0), at(resolution, 1));

    { // Computing terrain.
        using namespace maths;

        auto ci_to_x = maths::mapping(maths_impl::interval_0_n(at(resolution, 0)), xd);
        auto ri_to_y = maths::mapping(maths_impl::interval_0_n(at(resolution, 1)), yd);

        for(auto&& [ci, ri] : maths::row_major_indexes_cr(heights)) {
            auto x = ci_to_x(ci);
            auto y = ri_to_y(ri);
            using namespace terrain;
            auto [h, n] = decl::make<height_, normal_>(ter, vec2f({x, y}));
            at_cr(heights, ci, ri) = h;
            at_cr(normals, ci, ri) = n / 2.f + 0.5f;
        }
        
    }
    { // Outputting heights.
        auto f = io_std::open_file(
            std::string(terrain::output_folder) + "/mesh.obj",
            std::ios::binary | std::ios::out);
        auto w = terrain::wavefront(maths_impl::view(heights));
        w.x_domain = xd;
        w.y_domain = yd;
        io_format::wavefront::write(f, w);
    }
    { // Ouputting normals.
        io_qt::to_image(normals).save(QString(terrain::output_folder) + "/normals.png");;
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
