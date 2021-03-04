#pragma once

#include "imports.hpp"
#include "paths.hpp"

#include "pom/io_format/srtm/all.hpp"
#include "pom/io_std/all.hpp"
#include "pom/maths/matrix/all.hpp"
#include "pom/maths_impl/all.hpp"

namespace pom {
namespace terrain {

struct himalayas {
	himalayas() {
        auto file = io_std::open_file(
            std::string(input_folder) + "/srtmgl3_v003_hgt/n28e083.hgt",
            std::ios::binary | std::ios::in);
        data = io_format::srtm::read_srtm3(file);
        x_domain = y_domain = maths_impl::interval_0_n(1201.f * 90.f);
	}

	mat<float> data;
	interval<float> x_domain = maths_impl::interval_0_1<float>();
	interval<float> y_domain = maths_impl::interval_0_1<float>();
};

float weight(himalayas& h, vec2f xy) {
	return 1.f;
}

float height(himalayas& h, vec2f xy) {
	return maths::bilerp_normalized_cr(
		h.data,
		maths::normalized(h.x_domain, at(xy, 0)),
		maths::normalized(h.y_domain, at(xy, 1)));
}

vec2f gradient(himalayas& h, vec2f xy) {

}

vec2f normal(himalayas& h, vec2f xy) {

}

}}
