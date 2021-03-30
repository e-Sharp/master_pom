#pragma once

#include "imports.hpp"
#include "paths.hpp"

#include "pom/io_format/srtm/all.hpp"
#include "pom/io_std/all.hpp"
#include "pom/maths/matrix/all.hpp"
#include "pom/maths/gradient.hpp"
#include "pom/maths_impl/all.hpp"
#include "pom/maths/noise.hpp"

#include <iostream>

namespace pom {
namespace terrain {

struct dune {
	dune() {
        x_domain = y_domain = maths_impl::interval_0_n(10.f);
	}

	interval<float> x_domain = maths_impl::interval_0_1<float>();
	interval<float> y_domain = maths_impl::interval_0_1<float>();
};

constexpr
auto wyvill_fall_off_filter(point c, float r) {
    auto rr = r * r;
    return [c, rr](point p) {
        auto dd = (at(p, 0) - at(c, 0)) * (at(p, 0) - at(c, 0)) + (at(p, 1) - at(c, 1)) * (at(p, 1) - at(c, 1));
        auto p1 = rr - dd;
        return p1 > 0.f ? p1 * p1 * p1 : 0.f;
    };
}

float weight(vec2f xy) {
	//return 1.f;
    auto p = point{{at(xy, 0), at(xy, 1)}};
    return wyvill_fall_off_filter(point{{0, 0}}, 1.f)(p)};
}

float height(vec2f xy) {
    //return maths::perlin(point{{at(xy, 0), at(xy, 1)}});
    auto p = point{{at(xy, 0), at(xy, 1)}};
    return maths::fbm([](point p) { return maths::perlin(p); }, 5, p) * weight(p);
}
}}