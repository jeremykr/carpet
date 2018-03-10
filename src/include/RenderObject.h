#pragma once
#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Camera.h"

class RenderObject {
public:
    RenderObject();
    
    virtual void draw(Camera* camera);
    virtual void move(glm::vec3 d);
    virtual void rotate(float angle, glm::vec3 axis, bool useRadians=false);

    glm::vec3 pos = glm::vec3(0, 0, 0);
    glm::vec3 scale = glm::vec3(1, 1, 1);
    glm::quat quat;

protected:
    GLuint pid, vbo;
};