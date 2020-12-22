#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

#include "pom/ctree/global_prim.hpp"
#include "pom/ctree/modulation_op.hpp"
#include "pom/ctree/warping_op.hpp"

template<typename Ty>
constexpr auto pi = static_cast<Ty>(3.14159265359L);

template<typename Ty>
auto constant_f(Ty value) {
    return [value](point) {
        return value;
    };
}

auto radial_cos(point p) {
    auto x = 2.f * pi<float> * p[0];
    auto y = 2.f * pi<float> * p[1];
    return std::cos(std::sqrt(x * x + y * y));
}

constexpr
auto wyvill_fall_off_filter(float r) {
    auto rr = r * r;
    return [rr](point p) {
        auto dd = p[0] * p[0] + p[1] * p[1];
        auto p1 = rr - dd;
        return p1 > 0.f ? p1 * p1 * p1 : 0.f;
    };
}

float index(unsigned index, float min, float max, float resolution) {
    return (index / (resolution - 1)) * (max - min) + min;
}

struct vector3 {
    float x, y, z;
    vector3()
        : x(0)
        , y(0)
        , z(0)
    {}
    vector3(float a, float b, float c)
        : x(a)
        , y(b)
        , z(c)
    {}
};

void tesselation(shared_ctree tree, unsigned width, unsigned height,
                 int min, int max, int resolution, std::string name)
{
    std::ofstream objfile;
    std::vector<float> vertex(resolution * resolution);
    objfile.open(name + ".OBJ");
    if(!objfile.is_open()){
        std::cout << "failed to open file" << std::endl;
    }
    else{
        for(auto i = 0; i < resolution; ++i) {
            for(auto j = 0; j < resolution; ++j) {
                vertex[resolution * j + i] = tree->eval_at({index(i, min, max, resolution), index(j, min, max, resolution)}).height;
                objfile << "v " << index(i, min, max, resolution) << " "; 
                objfile << index(j, min, max, resolution) << " ";
                objfile << vertex[resolution * j + i] << "\n";
            }
        }
        std::vector<int> faces(resolution * resolution);
        for (auto i = 0; i < faces.size(); ++i) {
            faces[i] = i + 1;
        }

        for (auto i = 0; i < resolution - 1; ++i) {
            for (auto j = 0; j < resolution - 1; ++j) {
                objfile << "f " << faces[resolution * j + i] << " ";
                objfile << faces[resolution * j + (i + 1)] << " " ;
                objfile << faces[resolution * (j + 1) + i] << "\n";
                objfile << "f " << faces[resolution * j + (i + 1)] << " ";
                objfile << faces[resolution * (j + 1) + i] << " ";
                objfile << faces[resolution * (j + 1) + (i + 1)] << "\n";
            }
        }
    }

}

int main() {
    // [-2, 2]^2 100^2
    auto wyvill_t = shared_ctree(new global_prim{
        wyvill_fall_off_filter(1.f),
        [](point) { return 1.f; }
    });

    // [-5, 5]^2 500^2
    auto warped_wyvill_t = shared_ctree(new warping_op{
        [](point p) {
            auto d = distance(p);
            return point{d * p[0], d * p[1]};
        },
        wyvill_t
    });

    // [-5, 5]^2 500^2
    auto squared_warped_wyvill_t = shared_ctree(new modulation_op{
        [](float h) { return h * h; },
        warped_wyvill_t
    });

    std::cout << wyvill_t->eval_at({1, 0}).height << std::endl;
    constexpr unsigned width = 4;
    constexpr unsigned height = 4;
    tesselation(wyvill_t, 4, 4, -2, 2, 101, "wyvill_t");
    tesselation(warped_wyvill_t, 10, 10, -5, 5, 501, "warped_wyvill_t");
    tesselation(squared_warped_wyvill_t, 10, 10, -5, 5, 501, "squared_warped_wyvill_t");

}
