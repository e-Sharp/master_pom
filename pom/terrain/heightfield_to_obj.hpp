#pragma once

#include "heightfield.hpp"

#include "pom/io_format/wavefront/all.hpp"
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

// 'obj' concept.

struct obj {
    const heightfield* operator->() const noexcept {
        return &impl;
    }

    const heightfield& impl;
};

auto f_range(const obj& o) {
    using namespace ranges;
    auto cc = col_count(o->heights);
    auto rs = ranges::views::ints(std::size_t{0}, row_count(o->heights) - 1);
    auto cs = ranges::views::ints(std::size_t{1}, cc);
    return views::for_each(rs, [=](auto r) {
        auto r0 = r * cc;
        auto r1 = (r + 1) * cc;
        return views::for_each(cs, [r0, r1](auto c) {
            auto v00 = r0 + c;
            auto v01 = r1 + c;
            auto v10 = r0 + c + 1;
            auto v11 = r1 + c + 1;
            return views::single(maths_impl::vector<2>({
                obj_f({v00, v11, v01}), obj_f({v00, v10, v11})}))
            | views::join;
        });
    });
}

auto v_range(const obj& o) {
    using namespace ranges;
    auto c_to_x = maths::mapping(maths_impl::interval_0_n(col_count(o->heights)), at(o->domain, 0));
    auto r_to_y = maths::mapping(maths_impl::interval_0_n(row_count(o->heights)), at(o->domain, 1));
    return views::for_each(maths::row_indexes(o->heights), [=](auto ri) {
        auto r = row(o->heights, ri);
        auto y = r_to_y(ri);
        return maths::col_indexes(o->heights) | views::transform([=](auto ci) {
            auto x = c_to_x(ci);
            auto z = at(r, ci);
            return obj_v{{x, y, z}};
        });
    });
}

auto vt_range(const obj& o) {
    using namespace ranges;
    auto c_to_u = maths::mapping(maths_impl::interval_0_n(col_count(o->heights) - 1), maths_impl::interval_0_1<float>());
    auto r_to_v = maths::mapping(maths_impl::interval_0_n(row_count(o->heights) - 1), maths_impl::interval_0_1<float>());
    return views::for_each(maths::row_indexes(o->heights), [=](auto ri) {
        auto v = r_to_v(ri);
        return maths::col_indexes(o->heights) | views::transform([=](auto ci) {
            auto u = c_to_u(ci);
            return obj_vt{{u, v}};
        });
    });
}

}}
