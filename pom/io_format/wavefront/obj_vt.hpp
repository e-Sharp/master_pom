#pragma once

#include "pom/io/exception/all.hpp"

#include <concepts>

namespace pom {
namespace io_format {
namespace wavefront {

template<typename VT>
concept obj_vt = requires(const VT vt) {
    { has_v(vt) } -> std::convertible_to<bool>;
    { has_w(vt) } -> std::convertible_to<bool>;

    { u(vt) } -> std::floating_point;
    { v(vt) } -> std::floating_point;
    { w(vt) } -> std::floating_point;
};

}}}
