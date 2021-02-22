#pragma once

#include "input_stream.hpp"
#include "obj_f.hpp"
#include "obj_v.hpp"
#include "obj_vt.hpp"

#include "pom/io/exception/all.hpp"

#include <concepts>
#include <ranges>

namespace pom {
namespace io_format {
namespace wavefront {

// I couldn't figure out a way to make concept with defaults
// so these have to be fully implemented even if they aren't fully used.

template<typename Obj>
concept obj = requires(const Obj o) {
    { f_stream(o) } -> input_stream;
    { v_stream(o) } -> input_stream;
    { vt_stream(o) } -> input_stream;
};

}}}
