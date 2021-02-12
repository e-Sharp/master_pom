#pragma once

#include "concept/all.hpp"

#include "pom/maths/interval/all.hpp"
#include "pom/terrain/heightfield.hpp"

#include <concepts>
#include <iomanip>
#include <ostream>

namespace pom {
namespace io {
namespace wavefront_format {

template<obj Obj>
void write(std::ostream& os, const Obj& o) {
    for(decltype(v_count(o)) i = 0; i < v_count(o); ++i) {
        auto&& v_ = v(o, i);
        os << "v " << x(v_) << " " << y(v_) << " " << z(v_) << "\n";
    }
    //for(decltype(vt_count(o)) i = 0; i < vt_count(o); ++i) {
    //    auto&& vt_ = v(o, i);
    //    os << "vt " << u(vt_) << " " << v(vt_) << "\n";
    //}
    for(decltype(f_count(o)) i = 0; i < f_count(o); ++i) {
        auto&& f_ = f(o, i);
        os << "f";
        for(decltype(count(f_)) j = 0; j < count(f_); ++j) {
            os << " " << v(f_, j);
            if(has_vt(f_)) os << "//" << vt(f_, j);
        }
        os << "\n";
    }
}

void write2(std::ostream& os, const terrain::heightfield& hf) {
    auto rx = at(size(hf.heights), 0);
    auto ry = at(size(hf.heights), 1);

    using maths_impl::interval_;
    auto c_to_x = maths::mapping(interval_{0.f, static_cast<float>(rx - 1)}, at(hf.domain, 0));
	auto r_to_y = maths::mapping(interval_{0.f, static_cast<float>(ry - 1)}, at(hf.domain, 1));

	for(std::size_t j = 0; j < ry; ++j) {
		auto y = r_to_y(j);
		for(std::size_t i = 0; i < rx; ++i) {
			auto x = c_to_x(i);
			os << "v " << x << " " << y << " " << at(hf.heights, {i, j}) << "\n";
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
