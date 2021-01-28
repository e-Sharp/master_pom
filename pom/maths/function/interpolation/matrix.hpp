#pragma once

#include "pom/maths/function/map/vector.hpp"
#include "pom/maths/function/fract.hpp"
#include "pom/maths/matrix/all.hpp"
#include "pom/maths/vector/all.hpp"

#include <cmath>
#include <iostream>

namespace pom {

template<typename MTr, typename VTr>
auto bilerp(const matrix<MTr>& m, const vector<VTr>& v) {
    /*auto i0 = mapped_d(i, [](auto e) { return std::max(std::floor(e), 0.f); });
    auto i1 = mapped_d(i, [](auto e) { return std::ceil(e); });
    auto f = mapped_d(i, [](auto e) { return fract(e);  });*/
    
    // Neare
    auto fi = std::max(std::floor(at(v, 0)), 0.f);
    auto fj = std::max(std::floor(at(v, 1)), 0.f);
    auto i = std::min(static_cast<std::size_t>(fi), size(m, col{}) - 1);
    auto j = std::min(static_cast<std::size_t>(fj), size(m, row{}) - 1);
    return at(m, col{i}, row{j});
}

} // namespace pom
