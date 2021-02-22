#pragma once

#include "pom/io/exception/all.hpp"

#include <concepts>

namespace pom {
namespace io_format {
namespace wavefront {

template<typename F>
concept obj_f = requires(const F cf) {
    { vertex_count(cf) } -> std::integral;

    { has_vn(cf) } -> std::convertible_to<bool>;
    { has_vt(cf) } -> std::convertible_to<bool>;

    { v(cf, decltype(vertex_count(cf)){}) } -> std::integral;
    { vn(cf, decltype(vertex_count(cf)){}) } -> std::integral;
    { vt(cf, decltype(vertex_count(cf)){}) } -> std::integral;
};

}}}
