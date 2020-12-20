#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

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

float function(float x, float y) {
    return cos(sqrt(x * x + y * y));
}

int main() {
    std::ofstream objfile;
    objfile.open("test.OBJ");

    if (!objfile.is_open()) {
        std::cout << "failed to open" << std::endl;
    }
    else {
        const unsigned width = 100;
        const unsigned height = 100;

        std::vector<float> vertex(width * height);

        //vertices
        for (auto i = 0; i < width; ++i) {
            for (auto j = 0; j < height; ++j) {
                vertex[width * j + i] = function(i, j);
                objfile << "v " << i << " " << j << " " << vertex[width * j + i] << "\n";
            }
        }

        std::vector<int> faces(width * height);
        for (auto i = 0; i < faces.size(); ++i) {
            faces[i] = i + 1;
        }

        //draw triangles
        for (auto i = 0; i < width - 1; ++i) {
            for (auto j = 0; j < height - 1; ++j) {
                objfile << "f " << faces[width * j + i] << " " << faces[width * j + (i + 1)] << " " << faces[width * (j + 1) + i] << "\n";
                objfile << "f " << faces[width * j + (i + 1)] << " " << faces[width * (j + 1) + i] << " " << faces[width * (j + 1) + (i + 1)] << "\n";
            }
        }
    }
}