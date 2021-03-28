#include "pom/io_format/wavefront/all.hpp"
#include "pom/io_qt/all.hpp"
#include "pom/io_std/all.hpp"
#include "pom/terrain/all.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace pom;
using namespace pom::terrain;

void throwing_main() {
    //auto ter = terrain::directional_waves();
    auto ter = dunes_0();

    auto resolution = maths::vector_of<std::size_t>(1000, 1000);
    auto xd = maths::interval<float>(0.f, 1000.f);
    auto yd = maths::interval<float>(0.f, 1000.f);


    auto heights = maths::matrix_cr<float>(at(resolution, 0), at(resolution, 1));
    auto normals = maths::matrix_cr<terrain::vec3f>(at(resolution, 0), at(resolution, 1));
    auto texture = maths::matrix_cr<terrain::vec3f>(at(resolution, 0), at(resolution, 1));

    { 
        std::cout << "--Computing." << std::endl;
        using namespace maths;

        auto ci_to_x = maths::mapping(maths::interval_0_n(at(resolution, 0)), xd);
        auto ri_to_y = maths::mapping(maths::interval_0_n(at(resolution, 1)), yd);

        for(auto&& [ci, ri] : maths::row_major_indexes_cr(heights)) {
            auto x = ci_to_x(ci);
            auto y = ri_to_y(ri);
            using namespace terrain;

            auto [h] = decl::make<height_>(ter, vec2f({x, y}));

            at_cr(heights, ci, ri) = h;
            //at_cr(normals, ci, ri) = n / 2.f + 0.5f;
            //at_cr(texture, ci, ri) = c;
        }
    }
    { 
        std::cout << "--Writing mesh." << std::endl;
        auto f = io_std::open_file(
            std::string(terrain::output_folder) + "/mesh.obj",
            std::ios::binary | std::ios::out);
        auto w = terrain::wavefront(maths::view(heights));
        w.x_domain = xd;
        w.y_domain = yd;
        io_format::wavefront::write(f, w);
        
    }
    //{ // Ouputting heights.
    //    io_qt::to_image(heights).save(QString(terrain::output_folder) + "/heights.png");
    //}
    //{ // Ouputting normals.
    //    auto filename = "/normals_" + std::to_string(a) + "_" + std::to_string(f) + ".png";
    //    io_qt::to_image(normals).save(QString(terrain::output_folder) + "/normals_" + std::to_string(a) + "_" + std::to_string(f) + ".png");
    //}
    //{ // Ouputting texture.
    //    auto filename = "/texture_" + std::to_string(a) + "_" + std::to_string(f) + ".png";
    //    io_qt::to_image(texture).save(QString(terrain::output_folder) + "/texture_" + std::to_string(a) + "_" + std::to_string(f) + ".png");
    //}
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
