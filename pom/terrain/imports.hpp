#pragma once

#include "pom/maths_impl/all.hpp"

namespace pom {
namespace terrain {

template<typename Ty>
using interval = maths_impl::interval<Ty>;

template<typename Ty>
using mat = decltype(maths_impl::matrix<Ty>());

template<typename Ty>
using vec2 = decltype(maths_impl::vector<Ty, 2>());

using vec2f = vec2<float>;

}}
