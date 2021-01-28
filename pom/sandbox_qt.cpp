#include "pom/ctree/global_prim.hpp"
#include "pom/ctree/modulation_op.hpp"
#include "pom/ctree/warping_op.hpp"
#include "pom/maths/function/noise.hpp"
#include "pom/maths/function/interpolation/matrix.hpp"
#include "pom/maths/function/map/vector.hpp"
#include "pom/maths/matrix/all.hpp"

#include <fstream>
#include <iostream>
#include <QImageReader>
#include <stdexcept>

using namespace pom;

float index(unsigned index, float min, float max, float resolution) {
    return (index / (resolution - 1)) * (max - min) + min;
}

template<typename F>
void tesselation(F f, int min, int max, int resolution, std::string name)
{
    resolution += 1;
    std::ofstream objfile;
    std::vector<float> vertex(resolution * resolution);
    objfile.open(name + ".OBJ");
    if(!objfile.is_open()) {
        throw std::runtime_error{"Failed to open file."};
    }
    std::cout << "--Outputing vertices." << std::endl;
    for(auto j = 0; j < resolution; ++j) {
        std::cout << "line " << j << "\n";
        auto index_y = index(j, min, max, resolution);
        for(auto i = 0; i < resolution; ++i) {
            auto index_x = index(i, min, max, resolution);
            auto index_z = resolution * j + i;
            vertex[index_z] = f({index_x, index_y});
            objfile << "v " << index_x << " ";
            objfile << index_y << " ";
            objfile << vertex[index_z] << "\n";
        }
    }
    std::vector<int> faces(resolution * resolution);
    for(auto i = 0; i < faces.size(); ++i) {
        faces[i] = i + 1;
    }
    std::cout << "--Outputing faces." << "\n";
    for(auto j = 0; j < resolution - 1; ++j) {
        std::cout << "line " << j << "\n";
        auto rj = resolution * j;
        auto rjj = resolution * (j + 1);
        for(auto i = 0; i < resolution - 1; ++i) {
            objfile << "f " << faces[rj + i] << " ";
            objfile << faces[rj + (i + 1)] << " ";
            objfile << faces[rjj + i] << "\n";
            objfile << "f " << faces[rj + (i + 1)] << " ";
            objfile << faces[rjj + i] << " ";
            objfile << faces[rjj + (i + 1)] << "\n";
        }
    }
}

void throwing_main() {
	auto img = QImageReader{"D:\\dataset\\nasa_images_png\\PIA18033~small.png"}.read();
	if(img.isNull()) {
		throw std::runtime_error{"Failed to open file."};
	}

    std::cout << "--Loading image." << std::endl;

	auto m = dynamic_matrix<float>{col{static_cast<std::size_t>(img.width())}, row{static_cast<std::size_t>(img.height())}};
	for(col c = {0}; c < img.width(); ++c)
	for(row r = {0}; r < img.height(); ++r) {
		auto col = img.pixelColor(static_cast<int>(c), static_cast<int>(r));
		at(m, c, r) = (col.red() + col.green() + col.blue()) * (255.f / 3.f);
	}

    std::cout << "--Tesselating." << std::endl;

    tesselation(
        [&m](point p) { return bilerp(m, p);  },
        -100, 640, 2000, "res.obj"
    );
}

int main() {
	try {
		throwing_main();
	} catch(const std::exception& e) {
		std::cerr << "std::exception: " << e.what() << std::endl;
		return -1;
	} catch(...) {
		std::cerr << "Unhandled exception." << std::endl;
		return -1;
	}
	return 0;
}
