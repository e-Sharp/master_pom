#pragma once

#include "pom/maths/matrix/all.hpp"

#include <QImage>

namespace pom {
namespace io_qt {

constexpr auto f_to_i(float f) {
    return static_cast<int>(255.f * f + 0.5f);
}

template<typename M>
QImage to_image(const M& m) {
    auto im = QImage(static_cast<int>(col_count(m)), static_cast<int>(row_count(m)), QImage::Format_RGB32);
    for(auto r : maths::row_indexes(m)) {
        for(auto c : maths::col_indexes(m)) {
            auto int_i = static_cast<int>(c);
		    auto int_j = static_cast<int>(r);
            auto col = at(row(m, r), c);
            im.setPixelColor(int_i, int_j, qRgba(f_to_i(at(col, 0)), f_to_i(at(col, 1)), f_to_i(at(col, 2)), 255));
        }
    }
    return im;
}

}}
