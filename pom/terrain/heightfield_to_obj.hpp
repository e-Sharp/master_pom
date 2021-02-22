#pragma once

#include "heightfield.hpp"

#include "pom/io_format/wavefront/all.hpp"
#include "pom/maths/interval/all.hpp"
#include "pom/maths/vector/all.hpp"
#include "pom/maths_impl/all.hpp"

#include <range/v3/all.hpp>

namespace pom {
namespace terrain {

// 'obj_f' concept.

struct obj_f {
    maths_impl::static_vector<std::size_t, 3> impl = {};
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

static_assert(io_format::wavefront::obj_f<obj_f>);

// 'obj_v' concept.

struct obj_v {
    maths_impl::static_vector<float, 3> impl = {};
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

static_assert(io_format::wavefront::obj_v<obj_v>);

// 'obj_vt' concept.

struct obj_vt {
    maths_impl::static_vector<float, 2> impl = {};
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

static_assert(io_format::wavefront::obj_vt<obj_vt>);

// 'f_stream' requirement of 'obj'.

struct f_stream_ {
    using vector = maths_impl::static_vector<std::size_t, 2>;

    obj_f get_a() {
        get = &f_stream_::get_b;
        auto a = r * col_count + c + 1;
        auto b = r * col_count + c + 2;
        auto c_ = (r + 1) * col_count + c + 1;
        return {{a, b, c_}};
    }

    obj_f get_b() {
        get = &f_stream_::get_a;
        auto a = r * col_count + c + 2;
        auto b = (r + 1) * col_count + c + 1;
        auto c_ = (r + 1) * col_count + c + 2;

        if(++c + 1 >= col_count) {
            c = 0;
            ++r;
        }

        return {{a, b, c_}};
    }

    std::size_t col_count = {};
    std::size_t row_count = {};
    
    std::size_t c = 0;
    std::size_t r = 0;
    
    decltype(&f_stream_::get_a) get = &f_stream_::get_a;
};

bool empty(const f_stream_& s) noexcept {
    return s.r + 1 >= s.row_count;
}

obj_f get(f_stream_& s) {
    return (s.*s.get)();
}

static_assert(io_format::wavefront::input_stream<f_stream_>);

// 'v_stream' requirement of 'obj'.

struct v_stream_ {
    using matrix = maths_impl::dynamic_matrix<float>;
    using index = maths_impl::static_vector<std::size_t, 2>;

    const heightfield& hf;

    std::size_t c = 0;
    std::size_t r = 0;

    using mapping = decltype(maths::mapping(maths_impl::interval<std::size_t>{}, maths_impl::interval<float>{}));
    mapping c_to_x = maths::mapping(maths_impl::interval_0_n(hf.heights.col_count()), at(hf.domain, 0));
    mapping r_to_y = maths::mapping(maths_impl::interval_0_n(hf.heights.row_count()), at(hf.domain, 1));
};

bool empty(const v_stream_& s) {
    return s.r == s.hf.heights.row_count();
}

obj_v get(v_stream_& s) {
    auto x = s.c_to_x(s.c);
    auto y = s.r_to_y(s.r);
    auto z = at(row(s.hf.heights, s.r), s.c);

    if(++s.c == s.hf.heights.col_count()) {
        s.c = 0;
        ++s.r;
    }

    return {{x, y, z}};
}

// 'vt_stream' requirement of 'obj'.

auto vt_stream_mapping(std::size_t max) {
    auto orig = maths_impl::interval{0.f, static_cast<float>(max) - 1.f};
    auto dx = 1.f / (2.f * static_cast<float>(max));
    auto dest = maths_impl::interval{dx, 1.f - dx};
    return maths::mapping(orig, dest);
}

struct vt_stream_ {
    std::size_t c_count;
    std::size_t r_count;

    std::size_t c = 0;
    std::size_t r = 0;

    decltype(vt_stream_mapping(c_count)) c_to_u =
        vt_stream_mapping(c_count);
    decltype(vt_stream_mapping(r_count)) r_to_v = 
        vt_stream_mapping(r_count);
};

bool empty(const vt_stream_& s) {
    return s.r == s.r_count;
}

obj_vt get(vt_stream_& s) {
    auto u = s.c_to_u(static_cast<float>(s.c));
    auto v = s.r_to_v(static_cast<float>(s.r));
    
    if(++s.c == s.c_count) {
        s.c = 0;
        ++s.r;
    }

    return {{u, v}};
}

// 'obj' concept.

struct obj {
    const heightfield& impl;
};

f_stream_ f_stream(const obj& o) {
    return f_stream_{o.impl.heights.col_count(), o.impl.heights.row_count()};
}

v_stream_ v_stream(const obj& o) {
    return v_stream_{o.impl};
}

vt_stream_ vt_stream(const obj& o) {
    return vt_stream_{o.impl.heights.col_count(), o.impl.heights.row_count()};
}

static_assert(io_format::wavefront::obj<obj>);

}}
