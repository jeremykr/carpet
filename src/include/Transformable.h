#pragma once
#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

/* 
    Classes that inherit from this class have a position
    vector and a rotation quaternion, which can either be
    set directly or changed locally using the `move` and 
    `rotate` methods.

    Could be (and maybe should be) further split into
    `Moveable` and `Rotatable`, as `Transformable` may
    suggest the ability to scale, which is not required
    of the `Camera` class and so is not implemented here.
*/
class Transformable {
public:
    void move(glm::vec3 direction);
    void rotate(float angle, glm::vec3 axis, bool useRadians=false);

    glm::vec3 pos = glm::vec3(0, 0, 0);
    glm::quat quat;

protected:
    Transformable();
};