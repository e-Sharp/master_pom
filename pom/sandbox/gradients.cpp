#include "pom/io_format/wavefront/all.hpp"
#include "pom/io_qt/all.hpp"
#include "pom/io_std/all.hpp"
#include "pom/maths/constants.hpp"
#include "pom/maths/interval/all.hpp"
#include "pom/maths/all.hpp"
#include "pom/terrain/all.hpp"

#include <pom/maths/noise/perlin.hpp>
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
    auto ter = terrain::eroded(terrain::sphere());

    auto resolution
    auto xd = maths::interval<float>(-1.1f, 1.1f);
    auto yd = maths::interval<float>(-1.1f, 1.1f);

    {
        auto m = maths::matrix_cr<float>(500, 500);
        auto ci_to_x = maths::mapping(maths::interval_0_n(col_count(m)), xd);
        auto ri_to_y = maths::mapping(maths::interval_0_n(row_count(m)), yd);
        for(auto&& [ci, ri] : maths::row_major_indexes_cr(m)) {
            auto x = ci_to_x(ci);
            auto y = ri_to_y(ri);
            at_cr(m, ci, ri) = height(ter, {x, y});
        }
        auto f = io_std::open_file(
            std::string(terrain::output_folder) + "/mesh.obj",
            std::ios::binary | std::ios::out);
        auto w = terrain::wavefront(maths::view(m));
        w.x_domain = xd;
        w.y_domain = yd;
        io_format::wavefront::write(f, w);
    }

    /*{
        using namespace maths;
        auto m = maths::matrix_cr<terrain::vec3f>(500, 500);
        auto ci_to_x = maths::mapping(maths::interval_0_n(col_count(m)), xd);
        auto ri_to_y = maths::mapping(maths::interval_0_n(row_count(m)), yd);
        for(auto&& [ci, ri] : maths::row_major_indexes_cr(m)) {
            auto x = ci_to_x(ci);
            auto y = ri_to_y(ri);
            at_cr(m, ci, ri) = color(ter, {x, y});
        }
        io_qt::to_image(m).save(QString(terrain::output_folder) + "/texture.png");;
    }*/
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
