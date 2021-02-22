#pragma once

#include "pom/io/exception/all.hpp"

#include <concepts>

namespace pom {
namespace io_format {
namespace wavefront {

template<typename V>
concept obj_v = requires(const V cv) {
    { has_w(cv) } -> std::convertible_to<bool>;

    { x(cv) } -> std::floating_point;
    { y(cv) } -> std::floating_point;
    { z(cv) } -> std::floating_point;
    { w(cv) } -> std::floating_point;
};

}}}
