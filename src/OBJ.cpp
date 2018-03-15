#include "OBJ.h"

// Parse a string of space-separated floating point values
// into a vector.
namespace OBJ {

// Parse a string from the .obj file into a float vector
std::vector<float> parseVec(const std::string& line) {
    std::vector<float> v;
    std::string element;
    char c;
    for (size_t i = 0; i < line.length(); i++) {
        c = line.at(i);
        if (c == ' ') {
            v.push_back(std::stof(element));
            element.clear();
        } else {
            element.push_back(c);
        }
    }
    v.push_back(std::stof(element));
    return v;
}

// Parse a string from the .obj file into a TriangleInfo object
TriangleInfo parseTriangle(const std::string& line) {
    char value [100];
    size_t valueSize = 0;
    char c;

    unsigned vIndex, vtIndex, vnIndex;
    // 0 : Position, 1 : Texture, 2: Normal
    unsigned valueType = 0;
    unsigned pointIndex = 0;
    TriangleInfo tinf;

    for (size_t i = 0; i < line.length(); i++) {
        c = line[i];
        if (c == '/') {
            // Parse read value as either a vertex position index
            // or a texture index
            value[valueSize] = '\0';
            if (valueType == 0) { // Vertex position index
                vIndex = atoi(value);
            } else if (valueType == 1) { // Texture index
                vtIndex = atoi(value);
            }
            valueSize = 0;
            valueType++;
        } else if (c == ' ' || i == line.length() - 1) {
            // Parse read value as a vertex normal index
            // and add the PointInfo into the TriangleInfo
            // object at the pointIndex
            if (i == line.length() - 1) {
                value[valueSize++] = c;
            }
            value[valueSize] = '\0';
            vnIndex = atoi(value);
            valueType = 0;
            valueSize = 0;
            PointInfo pinf;
            pinf.vIndex = vIndex;
            pinf.vtIndex = vtIndex;
            pinf.vnIndex = vnIndex;
            tinf.points[pointIndex] = pinf;
            if (i == line.length() - 1) {
                pointIndex = 0;
            } else {
                pointIndex++;
            }
        } else {
            value[valueSize++] = c;
        }
    }
    return tinf;
}

OBJ parseFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    OBJ obj;

    if (file.is_open()) {

        while (std::getline(file, line)) {

            if (line.length() > 6 && line.compare(0, 7, "mtllib ") == 0) {
                obj.mtllib = line.substr(7);

            } else if (line.length() > 1 && line.compare(0, 2, "o ") == 0) {
                obj.o = line.substr(2);

            } else if (line.length() > 1 && line.compare(0, 2, "v ") == 0) {
                obj.v.push_back(parseVec(line.substr(2)));

            } else if (line.length() > 1 && line.compare(0, 3, "vt ") == 0) {
                obj.vt.push_back(parseVec(line.substr(3)));

            } else if (line.length() > 1 && line.compare(0, 3, "vn ") == 0) {
                obj.vn.push_back(parseVec(line.substr(3)));

            } else if (line.length() > 6 && line.compare(0, 7, "usemtl") == 0) {
                obj.usemtl = line.substr(7);

            } else if (line.length() > 1 && line.compare(0, 2, "s ") == 0) {
                obj.s = line.substr(2);

            } else if (line.length() > 1 && line.compare(0, 2, "f ") == 0) {
                obj.f.push_back(parseTriangle(line.substr(2)));
            }
        }

        file.close();
    } else {
        std::cout << "Cannot open " << filename << std::endl;
    }
    return obj;
}}