#pragma once

#include "pom/maths/interval/all.hpp"
#include "pom/terrain/heightfield.hpp"

#include <iomanip>
#include <ostream>

namespace pom {
namespace io {
namespace wavefront {

void write(std::ostream& os, const terrain::heightfield& hf) {
    auto rx = size(hf.heights, col{});
    auto ry = size(hf.heights, row{});

    using maths_impl::interval_;
    auto c_to_x = maths::mapping(interval_<float>{0, static_cast<float>(rx - 1)}, at(hf.domain, 0));
	auto r_to_y = maths::mapping(interval_<float>{0, static_cast<float>(ry - 1)}, at(hf.domain, 1));

    os << std::setprecision(5);

	for(row r = {0}; r < ry; ++r) {
		auto y = r_to_y(r);
		for(col c = {0}; c < rx; ++c) {
			auto x = c_to_x(c);
			os << "v " << x << " " << y << " " << at(hf.heights, c, r) << "\n";
		}
	}

    for (auto j = 0; j < ry - 1; ++j) {
        auto rj = rx * j, rjj = ry * (j + 1);
        for (auto i = 0; i < rx - 1; ++i) {
            os << "f " << rj + i + 1 << " " << rj + (i + 1) + 1 << " " << rjj + i + 1 << "\n";
            os << "f " << rj + (i + 1) + 1 << " " << rjj + i + 1 << " " << rjj + (i + 1) + 1 << "\n";
        }
    }
}

}}}
