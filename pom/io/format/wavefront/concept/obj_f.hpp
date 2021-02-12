#pragma once

#include "pom/io/format/wavefront/exception/all.hpp"

#include <concepts>

namespace pom {
namespace io {
namespace wavefront_format {

template<typename F>
concept obj_f_core = requires(const F f) {
    // Must be equal to 3 or 4.
    { count(f) } -> std::integral;

    // Coordinates.
    
    { v(f, decltype(count(f)){}) } -> std::integral;
};

template<obj_f_core F> constexpr
bool has_vn(F) noexcept {
    return false;
}

template<obj_f_core F> constexpr
bool has_vt(F) noexcept {
    return false;
}

template<obj_f_core F, typename I> constexpr
auto vn(const F& f, I) -> decltype(v(f, I{})) {
    if(has_vn(f)) throw not_implemented{};
    else throw precondition_violation{};
}

template<obj_f_core F, typename I> constexpr
auto vt(const F& f, I) -> decltype(v(f, I{})) {
    if(has_vt(f)) throw not_implemented{};
    else throw precondition_violation{};
}

template<typename F>
concept obj_f = obj_f_core<F> && requires(const F f) {
    // Normals.

    // Defaults to 'false'.
    { has_vn(f) } -> std::convertible_to<bool>;
    // Required if 'has_vn(f)'.
    { vn(f, decltype(count(f)){}) } -> std::integral;

    // Texture coordinates.

    // Defaults to 'false'.
    { has_vt(f) } -> std::convertible_to<bool>;
    // Required if 'has_vt(f)'.
    { vt(f, decltype(count(f)){}) } -> std::integral;
};

}}}
