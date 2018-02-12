#pragma once
#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class RenderObject {
public:
    RenderObject();
    virtual void draw() = 0;
    virtual void move(glm::vec3 d);
    virtual void setPosition(glm::vec3 p);
    virtual void rotate(glm::quat q);
    virtual void setRotation(glm::quat q);
private:
    GLuint pid, vbo;
    glm::vec3 pos = glm::vec3(0, 0, 0);
    glm::vec3 scale = glm::vec3(1, 1, 1);
    glm::quat quat;
};