#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

#include "pom/ctree/global_prim.hpp"
#include "pom/ctree/modulation_op.hpp"
#include "pom/ctree/warping_op.hpp"
#include "pom/maths/function/noise.hpp"

template<typename Ty>
constexpr auto pi = static_cast<Ty>(3.14159265359L);

template<typename Ty>
auto constant_f(Ty value) {
    return [value](point) {
        return value;
    };
}

auto radial_cos(point p) {
    auto x = 2.f * pi<float> * at(p, 0);
    auto y = 2.f * pi<float> * at(p, 1);
    return std::cos(std::sqrt(x * x + y * y));
}

constexpr
auto wyvill_fall_off_filter(float r) {
    auto rr = r * r;
    return [rr](point p) {
        auto dd = dot(p, p);
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

void tesselation(shared_ctree tree, unsigned, unsigned,
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
    auto perlin_t = shared_ctree(new global_prim{
        [](point p) { return pom::noise::fbm([](point p) { return pom::noise::perlin(p); }, 10, p); },
        [](point) { return 1.f; }
    });

    tesselation(perlin_t, 0, 0, -2, 2, 1200, "perlin_t");
}

// int main() {
//     // [-2, 2]^2 100^2
//     auto wyvill_t = shared_ctree(new global_prim{
//         wyvill_fall_off_filter(1.f),
//         [](point) { return 1.f; }
//     });

//     // [-5, 5]^2 500^2
//     auto rcos_t = shared_ctree(new global_prim{
//         radial_cos,
//         [](point) { return 1.f; }
//     });

//     // [-5, 5]^2 500^2
//     auto warped_rcos_t = shared_ctree(new warping_op{
//         [](point p) {
//             auto d = sqrt(distance(p));
//             if(d != 0) return point{p[0] / d, p[1] / d};
//             else return point{0, 0};
//         },
//         rcos_t
//     });

//     // [-5, 5]^2 500^2
//     auto squared_warped_rcos_t = shared_ctree(new modulation_op{
//         [](float h) { return h * h; },
//         warped_rcos_t
//     });

//     std::cout << wyvill_t->eval_at({1, 0}).height << std::endl;
//     constexpr unsigned width = 4;
//     constexpr unsigned height = 4;
//     tesselation(wyvill_t, 4, 4, -2, 2, 101, "wyvill_t");
//     tesselation(rcos_t, 10, 10, -5, 5, 501, "rcos_t");
//     tesselation(warped_rcos_t, 10, 10, -5, 5, 501, "warped_rcos_t");
//     tesselation(squared_warped_rcos_t, 10, 10, -5, 5, 501, "squared_warped_rcos_t");

// }
