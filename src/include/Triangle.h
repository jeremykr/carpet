#pragma once
#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <string>
#include "RenderObject.h"

class Triangle : public RenderObject {
public:
    Triangle();
    void draw() override;
private:
    GLuint pid;
    GLuint vbo;
};