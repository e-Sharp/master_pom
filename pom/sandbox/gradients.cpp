#include "pom/io_qt/all.hpp"
#include "pom/io_std/all.hpp"
#include "pom/io_format/srtm/all.hpp"
#include "pom/io_format/wavefront/all.hpp"
#include "pom/maths/matrix/interpolation.hpp"
#include "pom/maths/vector/all.hpp"
#include "pom/maths/gradient.hpp"
#include "pom/maths/noise.hpp"
#include "pom/maths/numeric.hpp"
#include "pom/terrain/all.hpp"
#include "pom/terrain/examples.hpp"
#include "pom/terrain/imports.hpp"
#include "pom/terrain/paths.hpp"

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

using namespace pom;
using namespace pom::maths;
using namespace pom::maths_impl;
using namespace pom::terrain;



void throwing_main() {
    
}

int main() {
    try {
        throwing_main();
    } catch(const std::exception& e) {
        std::cerr << "std::exception: " << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Unhandled exception." << std::endl;
        return -1;
    }
    return 0;
}
