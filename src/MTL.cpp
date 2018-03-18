#include "Wavefront.h"

namespace Wavefront {

MTL parseMTLFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    MTL mtl {
        "",
        100.0, 1.0, 1.0,
        std::vector<float> {1, 1, 1},
        std::vector<float> {.5, .5, .5},
        std::vector<float> {.5, .5, .5},
        std::vector<float> {0, 0, 0},
        2
    };

    std::string msg = "Error while parsing .mtl file " + filename + ": ";

    if (file.is_open()) {

        while (std::getline(file, line)) {
            
            if (line.length() > 6 && line.compare(0, 7, "newmtl ") == 0) {
                try { mtl.newmtl = line.substr(7); }
                catch (const std::exception& e) {}
            
            } else if (line.length() > 2 && line.compare(0, 3, "Ns ") == 0) {
                try { mtl.Ns = std::stof(line.substr(3)); }
                catch (const std::exception& e) {}

            } else if (line.length() > 2 && line.compare(0, 3, "Ka ") == 0) {
                try { mtl.Ka = parseVec(line.substr(3)); }
                catch (const std::exception& e) {}

            } else if (line.length() > 2 && line.compare(0, 3, "Kd ") == 0) {
                try { mtl.Kd = parseVec(line.substr(3)); }
                catch (const std::exception& e) {}

            } else if (line.length() > 2 && line.compare(0, 3, "Ks ") == 0) {
                try { mtl.Ks = parseVec(line.substr(3)); }
                catch (const std::exception& e) {}

            } else if (line.length() > 2 && line.compare(0, 3, "Ke ") == 0) {
                try { mtl.Ke = parseVec(line.substr(3)); }
                catch (const std::exception& e) {}

            } else if (line.length() > 2 && line.compare(0, 3, "Ni ") == 0) {
                try { mtl.Ni = std::stof(line.substr(3)); }
                catch (const std::exception& e) {}

            } else if (line.length() > 1 && line.compare(0, 2, "d ") == 0) {
                try { mtl.d = std::stof(line.substr(1)); }
                catch (const std::exception& e) {}

            } else if (line.length() > 5 && line.compare(0, 6, "illum ") == 0) {
                try { mtl.illum = std::stof(line.substr(6)); }
                catch (const std::exception& e) {}
            }
        }
    }

    file.close();
    return mtl;
}}