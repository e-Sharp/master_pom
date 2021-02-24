#pragma once

#include "obj.hpp"

#include "pom/maths/interval/all.hpp"
#include "pom/terrain/heightfield.hpp"

#include <concepts>
#include <iomanip>
#include <ostream>

namespace pom {
namespace io_format {
namespace wavefront {

template<typename Obj>
void write_all_f(std::ostream& os, const Obj& o) {
    for(auto&& f : f_range(o)) {
        os << "f";
        for(decltype(vertex_count(f)) i = 0; i < vertex_count(f); ++i) {
            os << " " << v(f, i);
            if(has_vt(f)) os << "/" << vt(f, i);
        }
        os << "\n";
    }
}

template<typename Obj>
void write_all_v(std::ostream& os, const Obj& o) {
    for(auto&& v : v_range(o)) {
        os << "v " << x(v) << " " << y(v) << " " << z(v) << "\n";
    }
}

template<typename Obj>
void write_all_vt(std::ostream& os, const Obj& o) {
    for(auto&& vt : vt_range(o)) {
        os << "vt " << u(vt);
        if(has_v(vt)) {
            os << " " << v(vt);
            if(has_w(vt)) os << " " << w(vt);
        }
        os << '\n';
    }
}

template<typename Obj>
void write(std::ostream& os, const Obj& o) {
    write_all_v(os, o);
    write_all_vt(os, o);
    write_all_f(os, o);
}

}}}
