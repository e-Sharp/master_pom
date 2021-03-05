#include "pom/io_format/wavefront/all.hpp"
#include "pom/io_std/all.hpp"
#include "pom/maths/interval/all.hpp"
#include "pom/maths/matrix/all.hpp"
#include "pom/maths/vector/all.hpp"
#include "pom/maths_impl/all.hpp"
#include "pom/terrain/imports.hpp"
#include "pom/terrain/paths.hpp"
#include "pom/terrain/wavefront.hpp"

using namespace pom;

float f(float x, float y) {
    auto d = maths::length(maths_impl::vector<2>({x, y}));
    auto dd = 1.f - d;
    if(d >= 1.f) return 0.f;
    else         return dd * dd * dd;
}

void throwing_main() {
    auto m = maths_impl::matrix_cr<float>(4, 3);

    auto xd = maths_impl::interval<float>(-1.f, 1.f);
    auto yd = maths_impl::interval<float>(-1.f, 1.f);

    auto ci_to_x = maths::mapping(maths_impl::interval_0_n(col_count(m) - 1), xd);
    auto ri_to_y = maths::mapping(maths_impl::interval_0_n(row_count(m) - 1), xd);

    for(auto&& [ci, ri] : maths::row_major_indexes_cr(m)) {
        at_cr(m, ci, ri) = f(ci_to_x(ci), ri_to_y(ri));
    }

    auto w = terrain::wavefront(std::move(m));
    w.x_domain = xd;
    w.y_domain = yd;

    auto f = io_std::open_file(std::string(terrain::output_folder) + "/erosion_brush.obj", std::ios::out);
    io_format::wavefront::write(f, w);
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
