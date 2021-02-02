#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

#include "pom/ctree/all.hpp"
#include "pom/maths/function/noise.hpp"
#include "pom/maths/function/vector/all.hpp"

using namespace pom::ctree;
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



template<typename T>
void tesselation(const T& tree, float min, float max, int resolution, std::string name) {
    resolution += 1;
    std::ofstream objfile;
    std::vector<float> vertex(resolution * resolution);
    objfile.open(name + ".OBJ");
    if(!objfile.is_open()) {
        std::cout << "failed to open file" << std::endl;
    }
    else{
        for(auto j = 0; j < resolution; ++j) {
            float index_y = j * ((max - min) / (resolution - 1))  + min;
            std::cout << "line " << j << std::endl;
            for(auto i = 0; i < resolution; ++i) {
                float index_x = i * ((max - min) / (resolution - 1))  + min;
                auto index_z = resolution * j +i;
                vertex[index_z] = tree({{index_x, index_y}}).value;
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
            std::cout << "line " << j << std::endl;
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

constexpr
auto spiral_warping(point c, float r, float rotation) {
    auto rr = r * r;
    return[c, rr, rotation](point p) {
        auto dd = (at(p, 0) - at(c, 0)) * (at(p, 0) - at(c, 0)) + (at(p, 1) - at(c, 1)) * (at(p, 1) - at(c, 1));
        if(dd < rr) {
            //cart to polar
            auto d = sqrt(at(p, 0) * at(p, 0) + at(p, 1) * at(p,1));
            auto a = atan2(at(p,1), at(p, 0));

            auto p1 = rr - dd;
            auto influence =  p1 > 0.f ? p1 * p1 * p1 : 0.f;
            //angle pour willy
            auto angle = a + rotation * influence;

            //polar to cart
            at(p, 0) = d * cos(angle);
            at(p, 1) = d * sin(angle);
        }
    };
}

int main() {
    auto perlin_t = [](point p) {
        return eval{
            .value = fbm([](point p) { return perlin(p); }, 5, p),
            .weight = wyvill_fall_off_filter(point{{0, 0}}, 1.f)(p)};
    };

    auto weighted_perlin_t = modulation(perlin_t, [](eval e) {
        e.value *= e.weight;
        return e;
    });

    tesselation(weighted_perlin_t, -2, 2, 200, "weighted_perlin_t");
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
