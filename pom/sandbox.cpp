#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

#include "pom/ctree/global_prim.hpp"
#include "pom/ctree/modulation_op.hpp"
#include "pom/ctree/warping_op.hpp"
#include "pom/maths/function/noise.hpp"
#include "pom/maths/function/vector/all.hpp"

using namespace pom::maths;

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

constexpr
auto wyvill_fall_off_filter(point c, float r) {
    auto rr = r * r;
    return [c, rr](point p) {
        auto dd = (at(p, 0) - at(c, 0)) * (at(p, 0) - at(c, 0)) + (at(p, 1) - at(c, 1)) * (at(p, 1) - at(c, 1));
        //auto dd = dot(c, p);
        auto p1 = rr - dd;
        return p1 > 0.f ? p1 * p1 * p1 : 0.f;
    };
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

float index(unsigned index, float min, float max, float resolution) {
    return (index / (resolution - 1)) * (max - min) + min;
}


void tesselation(shared_ctree tree,
                 int min, int max, int resolution, std::string name)
{
    resolution += 1;
    std::ofstream objfile;
    std::vector<float> vertex(resolution * resolution);
    objfile.open(name + ".OBJ");
    if(!objfile.is_open()){
        std::cout << "failed to open file" << std::endl;
    }
    else{
        for(auto j = 0; j < resolution; ++j) {
            for(auto i = 0; i < resolution; ++i) {
                auto index_x = index(i, min, max, resolution);
                auto index_y = index(j, min, max, resolution);
                auto index_z = resolution * j +i;
                vertex[index_z] = tree->eval_at({{index_x, index_y}}).height;
                objfile << "v " << index_x << " "; 
                objfile << index_y << " ";
                objfile << vertex[index_z] << "\n";
            }
        }
        std::vector<int> faces(resolution * resolution);
        for (auto i = 0; i < faces.size(); ++i) {
            faces[i] = i + 1;
        }

        for (auto j = 0; j < resolution - 1; ++j) {
            for (auto i = 0; i < resolution - 1; ++i) {
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
        [](point p) { return fbm([](point p) { return perlin(p); }, 10, p); },
        wyvill_fall_off_filter(point{{0, 0}}, 1.f)
    });

    auto weighted_perlin_t = shared_ctree(new global_prim{
        [perlin_t](point p) {
            auto e = perlin_t->eval_at(p);
            return e.height * e.weight;
        },
        [](point) { return 1.f; }
    });

    tesselation(perlin_t, -2, 2, 1000, "perlin_t");
}

// int main() {
//     // [-2, 2]^2 100^2
//     auto wyvill_t = shared_ctree(new global_prim{
//         wyvill_fall_off_filter(1.f),
//         [](point) { return 1.f; }
//     });

//     // // [-5, 5]^2 500^2
//     // auto rcos_t = shared_ctree(new global_prim{
//     //     radial_cos,
//     //     [](point) { return 1.f; }
//     // });

//     // // [-5, 5]^2 500^2
//     // auto warped_rcos_t = shared_ctree(new warping_op{
//     //     [](point p) {
//     //         auto d = sqrt(distance(p));
//     //         if(d != 0) return point{p[0] / d, p[1] / d};
//     //         else return point{0, 0};
//     //     },
//     //     rcos_t
//     // });

//     // // [-5, 5]^2 500^2
//     // auto squared_warped_rcos_t = shared_ctree(new modulation_op{
//     //     [](float h) { return h * h; },
//     //     warped_rcos_t
//     // });

//     std::cout << wyvill_t->eval_at({1, 0}).height << std::endl;
//     constexpr unsigned width = 4;
//     constexpr unsigned height = 4;
//     tesselation(wyvill_t, -2, 2, 100, "wyvill_t");
//     // tesselation(rcos_t, 10, 10, -5, 5, 500, "rcos_t");
//     // tesselation(warped_rcos_t, 10, 10, -5, 5, 500, "warped_rcos_t");
//     // tesselation(squared_warped_rcos_t, 10, 10, -5, 5, 500, "squared_warped_rcos_t");

// }
