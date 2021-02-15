#pragma once

#include "heightfield.hpp"

#include "pom/io/wavefront/all.hpp"
#include "pom/maths/interval/all.hpp"
#include "pom/maths/vector/all.hpp"
#include "pom/maths_impl/all.hpp"

namespace pom {
namespace terrain {

// 'obj_f' concept.

struct obj_f {
    maths_impl::static_vector_<std::size_t, 3> impl = {};
};

constexpr std::size_t vertex_count(const obj_f& f) noexcept {
    return size(f.impl);
}

constexpr bool has_vn(const obj_f&) noexcept {
    return false;
}

constexpr bool has_vt(const obj_f&) noexcept {
    return true;
}

constexpr auto v(const obj_f& f, std::size_t i) {
    return at(f.impl, i);
}

constexpr auto vt(const obj_f& f, std::size_t i) {
    return v(f, i);
}

std::size_t vn(const obj_f&, std::size_t) {
    throw io::not_implemented{};
}

static_assert(io::wavefront::obj_f<obj_f>);

// 'obj_v' concept.

struct obj_v {
    maths_impl::static_vector_<float, 3> impl = {};
};

constexpr bool has_w(const obj_v&) {
    return false;
}

constexpr auto x(const obj_v& v) {
    return at(v.impl, 0);
}

constexpr auto y(const obj_v& v) {
    return at(v.impl, 1);
}

constexpr auto z(const obj_v& v) {
    return at(v.impl, 2);
}

float w(const obj_v&) {
    throw io::not_implemented{};
}

static_assert(io::wavefront::obj_v<obj_v>);

// 'obj_vt' concept.

struct obj_vt {
    maths_impl::static_vector_<float, 2> impl = {};
};

constexpr bool has_v(const obj_vt&) noexcept {
    return true;
}

constexpr bool has_w(const obj_vt&) noexcept {
    return false;
}

constexpr auto u(const obj_vt& vt) {
    return at(vt.impl, 0);
}

constexpr auto v(const obj_vt& vt) {
    return at(vt.impl, 1);
}

float w(const obj_vt&) {
    throw io::not_implemented{};
}

static_assert(io::wavefront::obj_vt<obj_vt>);

// 'f_stream' requirement of 'obj'.

struct f_stream_ {
    using vector = maths_impl::static_vector_<std::size_t, 2>;

    obj_f get_a() {
        get = &f_stream_::get_b;
        auto a = at(index, 1) * at(size, 0) + at(index, 0) + 1;
        auto b = at(index, 1) * at(size, 0) + at(index, 0) + 2;
        auto c = (at(index, 1) + 1) * at(size, 0) + at(index, 0) + 1;
        return {{a, b, c}};
    }

    obj_f get_b() {
        get = &f_stream_::get_a;
        auto a = at(index, 1) * at(size, 0) + at(index, 0) + 2;
        auto b = (at(index, 1) + 1) * at(size, 0) + at(index, 0) + 1;
        auto c = (at(index, 1) + 1) * at(size, 0) + at(index, 0) + 2;

        if(++at(index, 0) + 1 >= at(size, 0)) {
            at(index, 0) = 0;
            ++at(index, 1);
        }

        return {{a, b, c}};
    }

    vector size = {};
    vector index = {0, 0};
    
    decltype(&f_stream_::get_a) get = &f_stream_::get_a;
};

bool empty(const f_stream_& s) noexcept {
    return at(s.index, 1) + 1 >= at(s.size, 1);
}

obj_f get(f_stream_& s) {
    return (s.*s.get)();
}

static_assert(io::wavefront::input_stream<f_stream_>);

// 'v_stream' requirement of 'obj'.

struct v_stream_ {
    using interval = maths_impl::interval_<float>;
    using matrix = maths_impl::dynamic_matrix_<float>;
    using index = maths_impl::static_vector_<std::size_t, 2>;

    const heightfield& hf;

    index ij = {0, 0};

    using mapping = decltype(maths::mapping(interval{}, interval{}));
    mapping i_to_x = maths::mapping(interval{0, static_cast<float>(at(size(hf.heights), 0) - 1)}, at(hf.domain, 0));
    mapping j_to_y = maths::mapping(interval{0, static_cast<float>(at(size(hf.heights), 1) - 1)}, at(hf.domain, 1));
};

bool empty(const v_stream_& s) {
    return at(s.ij, 1) == at(size(s.hf.heights), 1);
}

obj_v get(v_stream_& s) {
    auto x = s.i_to_x(at(s.ij, 0));
    auto y = s.j_to_y(at(s.ij, 1));
    auto z = at(s.hf.heights, s.ij);

    if(++at(s.ij, 0) == at(size(s.hf.heights), 0)) {
        at(s.ij, 0) = 0;
        ++at(s.ij, 1);
    }

    return {{x, y, z}};
}

// 'vt_stream' requirement of 'obj'.

auto vt_stream_mapping(std::size_t max) {
    auto orig = maths_impl::interval_{0.f, static_cast<float>(max) - 1.f};
    auto dest = maths_impl::interval_{0.f, 1.f};
    return maths::mapping(orig, dest);
}

struct vt_stream_ {
    maths_impl::static_vector_<std::size_t, 2> max = {};
    maths_impl::static_vector_<std::size_t, 2> ij = {0, 0};

    decltype(vt_stream_mapping(at(max, 0))) i_to_u =
        vt_stream_mapping(at(max, 0));
    decltype(vt_stream_mapping(at(max, 1))) j_to_v = 
        vt_stream_mapping(at(max, 1));
};

bool empty(const vt_stream_& s) {
    return at(s.ij, 1) == at(s.max, 1);
}

obj_vt get(vt_stream_& s) {
    auto u = s.i_to_u(static_cast<float>(at(s.ij, 0)));
    auto v = s.j_to_v(static_cast<float>(at(s.ij, 1)));
    
    if(++at(s.ij, 0) == at(s.max, 0)) {
        at(s.ij, 0) = 0;
        ++at(s.ij, 1);
    }

    return {{u, v}};
}

// 'obj' concept.

struct obj {
    const heightfield& impl;
};

f_stream_ f_stream(const obj& o) {
    using maths::operator-;
    return f_stream_{size(o.impl.heights)};
}

v_stream_ v_stream(const obj& o) {
    return v_stream_{o.impl};
}

vt_stream_ vt_stream(const obj& o) {
    return vt_stream_{size(o.impl.heights)};
}

static_assert(io::wavefront::obj<obj>);

}}
