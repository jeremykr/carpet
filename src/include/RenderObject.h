#pragma once
#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Wavefront.h"
#include "VertexLayout.h"
#include "Transformable.h"

class RenderObject : public Transformable {
public:
    RenderObject(
        const std::vector<GLfloat> data,
        const VertexLayout layout
    );
    
    virtual void draw(Camera* camera);

    glm::vec3 scale = glm::vec3(1, 1, 1);
    std::string tag;
    Wavefront::MTL material;

    static RenderObject fromOBJ(Wavefront::OBJ o);

protected:
    GLuint 
        vao,            // vertex attribute object
        vbo,            // vertex buffer object
        vsid,           // vertex shader id
        fsid,           // fragment shader id
        pid;            // shader program id
    const std::vector<GLfloat> data;
    const VertexLayout layout;
    unsigned vertexCount;
};