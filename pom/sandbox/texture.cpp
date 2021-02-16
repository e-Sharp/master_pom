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
	auto im = QImage(at(s, 0), at(s, 1), QImage::Format_RGB32);
	for(decltype(s) ij = {0, 0}; at(ij, 1) < at(s, 1); ++at(ij, 1)) {
		for(at(ij, 0) = 0; at(ij, 0) < at(s, 0); ++at(ij, 0)) {
			im.setPixelColor(at(ij, 0), at(ij, 1), qRgba(at(ij, 0), at(ij, 1), 0, 255));
		}
	}
	return im;
}

int main() {
	auto m = dynamic_matrix_<float>({255, 255});
	static_assert(matrix<decltype(m)>);
	auto i = to_image(m);
	i.save("texture.png");
}
