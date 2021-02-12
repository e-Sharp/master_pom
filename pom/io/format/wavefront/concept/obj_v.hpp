#pragma once

#include "pom/io/format/wavefront/exception/all.hpp"

#include <concepts>

namespace pom {
namespace io {
namespace wavefront_format {

template<typename V>
concept obj_v_core = requires(const V v) {
    { x(v) } -> std::floating_point;
    { y(v) } -> std::floating_point;
    { z(v) } -> std::floating_point;
};

template<obj_v_core V> constexpr
bool has_w(const V&) noexcept {
    return false;
}

template<obj_v_core V> constexpr
auto w(const V& v) -> decltype(x(v)) {
    if(has_w(v)) throw not_implemented{};
    else throw precondition_violation{};
}

template<typename V>
concept obj_v = obj_v_core<V> && requires(const V v) {
    // Defaults to 'false'.
    { has_w(v) } -> std::convertible_to<bool>;
    // Required if 'has_w(v)'.
    { w(v) } -> std::floating_point;
};

}}}
