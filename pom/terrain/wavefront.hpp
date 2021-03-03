#pragma once

#include "pom/maths/interval/all.hpp"
#include "pom/maths_impl/all.hpp"

#include <range/v3/view/enumerate.hpp>

namespace pom {
namespace terrain {

template<typename Matrix>
class wavefront {
public:
    constexpr wavefront(Matrix&& m)
        : heights(std::move(m))
    {}

    Matrix heights;

	maths_impl::interval<float> x_domain = maths_impl::interval_0_1<float>();
	maths_impl::interval<float> y_domain = maths_impl::interval_0_1<float>();
	maths_impl::interval<float> u_domain = maths_impl::interval_0_1<float>();
	maths_impl::interval<float> v_domain = maths_impl::interval_0_1<float>();
};

template<typename M>
wavefront(M) -> wavefront<M>; 

// Domain mapping.

template<typename M> constexpr
auto ci_to_x_mapping(const wavefront<M>& w) {
    return maths::mapping(
        maths_impl::interval_0_n(col_count(w.heights) - 1), w.x_domain);
}

template<typename M> constexpr
auto ri_to_y_mapping(const wavefront<M>& w) {
    return maths::mapping(
        maths_impl::interval_0_n(row_count(w.heights) - 1), w.y_domain);
}

template<typename M> constexpr
auto ci_to_u_mapping(const wavefront<M>& w) {
    return maths::mapping(
        maths_impl::interval_0_n(col_count(w.heights) - 1), w.u_domain);
}

template<typename M> constexpr
auto ri_to_v_mapping(const wavefront<M>& w) {
    return maths::mapping(
        maths_impl::interval_0_n(row_count(w.heights) - 1), w.v_domain);
}

//

struct wavefront_f {
    maths_impl::static_vector<std::size_t, 3> indexes = {};
};

constexpr std::size_t vertex_count(const wavefront_f& f) noexcept {
    return size(f.indexes);
}

constexpr bool has_vn(const wavefront_f&) noexcept {
    return false;
}

constexpr bool has_vt(const wavefront_f&) noexcept {
    return true;
}

constexpr auto v(const wavefront_f& f, std::size_t i) {
    return at(f.indexes, i);
}

constexpr auto vt(const wavefront_f& f, std::size_t i) {
    return v(f, i);
}

std::size_t vn(const wavefront_f&, std::size_t) {
    throw io::not_implemented{};
}

template<typename M> constexpr
auto f_range(const wavefront<M>& w) {
    auto cc = col_count(w.heights);
    auto rs = ranges::views::ints(std::size_t{0}, row_count(w.heights) - 1);
    auto cs = ranges::views::ints(std::size_t{1}, cc);
    return ranges::views::for_each(rs, [=](auto r) {
        auto r0 = r * cc;
        auto r1 = (r + 1) * cc;
        return ranges::views::for_each(cs, [r0, r1](auto c) {
            auto v00 = r0 + c;
            auto v01 = r1 + c;
            auto v10 = r0 + c + 1;
            auto v11 = r1 + c + 1;
            return ranges::views::single(maths_impl::vector<2>({
                wavefront_f({v00, v11, v01}), wavefront_f({v00, v10, v11})}))
            | ranges::views::join;
        });
    });
}

struct wavefront_v {
    maths_impl::static_vector<float, 3> values = {};
};

constexpr bool has_w(const wavefront_v&) {
    return false;
}

constexpr auto x(const wavefront_v& v) {
    return at(v.values, 0);
}

constexpr auto y(const wavefront_v& v) {
    return at(v.values, 1);
}

constexpr auto z(const wavefront_v& v) {
    return at(v.values, 2);
}

float w(const wavefront_v&) {
    throw io::not_implemented{};
}

template<typename M> constexpr
auto v_range(const wavefront<M>& w) {
    using namespace ranges::views;
    auto ci_to_x = ci_to_x_mapping(w);
    auto ri_to_y = ri_to_y_mapping(w);
    return for_each(rows(w.heights) | enumerate, [=](auto&& ri_r) {
            auto&& [ri, r] = ri_r;
            auto y = ri_to_y(ri);
            return single(std::move(r)) | join | enumerate
            | transform([=](auto&& ci_z) {
                auto&& [ci, z] = ci_z;
                auto x = ci_to_x(ci);
                return wavefront_v({x, y, z});
            });
        }
    );
}

struct wavefront_vt {
    maths_impl::static_vector<float, 2> impl = {};
};

constexpr bool has_v(const wavefront_vt&) noexcept {
    return true;
}

constexpr bool has_w(const wavefront_vt&) noexcept {
    return false;
}

constexpr auto u(const wavefront_vt& vt) {
    return at(vt.impl, 0);
}

constexpr auto v(const wavefront_vt& vt) {
    return at(vt.impl, 1);
}

float w(const wavefront_vt&) {
    throw io::not_implemented{};
}

template<typename M> constexpr
auto vt_range(const wavefront<M>& w) {
    auto ci_to_x = ci_to_x_mapping(w);
    auto ri_to_y = ri_to_y_mapping(w);
    return ranges::views::for_each(maths::row_indexes(w.heights), [=](auto ri) {
        auto v = ri_to_y(ri);
        return maths::col_indexes(w.heights)
        | ranges::views::transform([=](auto ci) {
            auto u = ci_to_x(ci);
            return wavefront_vt({u, v});
        });
    });
}

}}
