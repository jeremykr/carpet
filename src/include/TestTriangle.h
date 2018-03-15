#pragma once
#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <string>
#include "RenderObject.h"

class TestTriangle : public RenderObject {
public:
    TestTriangle();
    void draw(Camera* camera) override;
};