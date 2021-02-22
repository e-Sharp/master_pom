#include "pom/maths/matrix/all.hpp"
#include "pom/maths_impl/all.hpp"

#include <iostream>
#include <QImage>

using namespace pom;

using namespace maths;
using namespace maths_impl;

template<matrix M>
QImage to_image(const M& m) {
	auto s = size(m);
	auto im = QImage(static_cast<int>(at(s, 0)), static_cast<int>(at(s, 1)), QImage::Format_RGB32);
	for(decltype(s) ij = {0, 0}; at(ij, 1) < at(s, 1); ++at(ij, 1)) {
		for(at(ij, 0) = 0; at(ij, 0) < at(s, 0); ++at(ij, 0)) {
			auto int_i = static_cast<int>(at(ij, 0));
			auto int_j = static_cast<int>(at(ij, 1));
			im.setPixelColor(int_i, int_j, qRgba(at(ij, 0), at(ij, 1), 0, 255));
		}
	}
	return im;
}

int main() {
	auto s = dynamic_matrix_<float>({255, 255});
	auto mapping = [](float f) { return static_cast<int>(f); };
	auto d = mapped(s, mapping, dynamic_matrix_<int>{});
	
	static_assert(matrix<decltype(d)>);
	auto i = to_image(d);
	i.save("texture.png");
}
