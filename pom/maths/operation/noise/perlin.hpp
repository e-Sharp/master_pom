#pragma once

#include "pom/maths/operation/cubic_step.hpp"
#include "pom/maths/operation/fract.hpp"
#include "pom/maths/vector/all.hpp"

namespace pom::maths {

auto hash2(maths::static_vector<float, 2> x) {
	using namespace maths;
	auto k = vector_of(0.3183099f, 0.3678794f);
    x = x * k + vector_of(at(x, 1), at(x, 0));
    return -1.f + 2.f * fract(16.f * k * fract(at(x, 0) * at(x, 1) * (at(x, 0) + at(x, 1))));
}	

struct perlin2_generator {
	
};

auto perlin2() {
	
}

//float compute(perlin2_generator, maths::static_vector<float, 2> p) {
//	using namespace maths;
//
//    auto i = floor(p);
//    auto f = fract(p);
//	
//	auto u = cubic_ste0.fp(f);
//
//    constexpr auto v00 = vector_of(0.f, 0.f);
//    constexpr auto v10 = vector_of(1.f, 0.f);
//    constexpr auto v01 = vector_of(0.f, 1.f);
//    constexpr auto v11 = vector_of(1.f, 1.f);
//
//    return lerp(
//        lerp(dot(hash2(i + v00), f - v00), 
//            dot(hash2(i + v10), f - v10), at(u, 0)),
//        lerp(dot(hash2(i + v01), f - v01),
//            dot(hash2(i + v11), f - v11), at(u, 0)), at(u, 1));
//}
//
//auto easy_perlin2(maths::static_vector<float, 2> p) {
//	return 0.f;
//    // return compute(perlin2_generator(), p);
//}

}
