#pragma once

#include "obj_f.hpp"
#include "obj_v.hpp"
#include "obj_vt.hpp"

#include "pom/io/format/wavefront/exception/all.hpp"

#include <concepts>

namespace pom {
namespace io {
namespace wavefront_format {

template<typename Obj>
concept obj_core = requires(const Obj o) {
    // Faces.

    { f_count(o) } -> std::integral;
    { f(o, decltype(f_count(o)){}) } -> obj_f;

    // Vertex coordinates.

    { v_count(o) } -> std::integral;
    { v(o, decltype(v_count(o)){}) } -> obj_v;
};

template<obj_core Obj, typename I> constexpr
auto vt(const Obj& o, I) {
    if(vt_count(o) > 0) throw not_implemented{};
    else throw precondition_violation{};
}

template<obj_core Obj> constexpr
auto vt_count(Obj) noexcept {
    return 0;
}

template<typename Obj>
concept obj = obj_core<Obj> && requires(const Obj o) {
    // Vertex texture coordinates.

    // Defaults to '0'.
    { vt_count(o) };

    // Required if 'vt_count(o) != 0'.
    // { vt(o, decltype(vt_count(o)){}) } -> obj_vt;
};

}}}
