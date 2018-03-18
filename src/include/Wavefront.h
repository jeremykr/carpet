#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <stdexcept>

// Structs and functions for parsing a Wavefront .obj file
namespace Wavefront {

    struct PointInfo {
        unsigned vIndex, vtIndex, vnIndex;
    };

    struct TriangleInfo {
        PointInfo points [3];
    };

    struct OBJ {
        std::string mtllib;
        std::string o;
        std::vector<std::vector<float>> v;
        std::vector<std::vector<float>> vt;
        std::vector<std::vector<float>> vn;
        std::string usemtl;
        std::string s;
        std::vector<TriangleInfo> f;
    };

    OBJ parseOBJFile(const std::string& filename);
    std::vector<float> parseVec(const std::string& line);
    TriangleInfo parseTriangle(const std::string& line);

    struct MTL {
        std::string newmtl;
        float Ns, Ni, d;
        std::vector<float> Ka, Kd, Ks, Ke;
        unsigned illum;
    };

    MTL parseMTLFile(const std::string& filename);
}