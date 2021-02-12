#pragma once

#include "pom/io/format/wavefront/exception/all.hpp"

#include <concepts>

namespace pom {
namespace io {
namespace wavefront_format {

template<typename VT>
concept obj_vt = requires(const VT vt) {
    // Optional. Defaults to 'false'.
    { has_v(vt) } -> std::convertible_to<bool>;
    // Optional. Defaults to 'false'.
    { has_w(vt) } -> std::convertible_to<bool>;

    { u(vt) } -> std::floating_point;
    // Required if 'has_v(v)'.
    { v(vt) } -> std::floating_point;
    // Required if 'has_w(v)'.
    { w(vt) } -> std::floating_point;
};

template<obj_vt VT> constexpr
bool has_v(VT) noexcept {
    return false;
}

template<obj_vt VT> constexpr
bool has_w(VT) noexcept {
    return false;
}

template<obj_vt VT> constexpr
auto v(const VT& vt) {
    if(has_v(vt)) throw not_implemented{};
    else throw precondition_violation{};
}

template<obj_vt VT> constexpr
auto w(const VT& vt) {
    if(has_w(vt)) throw not_implemented{};
    else throw precondition_violation{};
}

}}}
