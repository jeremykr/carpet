#include "RenderObject.h"

void checkError() {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cout << "GL error: " << std::endl;
        switch (error) {
            case GL_INVALID_ENUM: std::cout << "Invalid enum"; break;
            case GL_INVALID_VALUE: std::cout << "Invalid value"; break;
            case GL_INVALID_OPERATION: std::cout << "Invalid operation"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: std::cout << "Invalid framebuffer operation"; break;
            case GL_OUT_OF_MEMORY: std::cout << "Out of memory"; break;
            default: std::cout << "Unknown error";
        }
        std::cout << std::endl;
    }
}

RenderObject::RenderObject(
    const std::vector<GLfloat> data,
    const VertexLayout layout
) :
    Transformable(),
    data(data), layout(layout)
{ 
    vertexCount = data.size() / (
        layout.positionDimensions +
        layout.textureDimensions +
        layout.normalDimensions
    );

    // Define shader sources
    const GLchar* vshaderSource = R"glsl(
    # version 330 core
    layout(location = 0) in vec3 vpos;
    layout(location = 1) in vec2 vuv;
    layout(location = 2) in vec3 vnorm;
    uniform mat4 MVP;
    out vec2 fuv;
    out vec3 fnorm; 
    void main() {
        gl_Position = MVP * vec4(vpos, 1.0);
        fuv = vuv;
        fnorm = vnorm;
    })glsl";

    const GLchar* fshaderSource = R"glsl(
    # version 330 core
    in vec2 fuv;
    in vec3 fnorm;
    out vec4 color;
    void main() {
        color = vec4(1,1,1,1);
    })glsl";

    // Setup vertex buffers
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLsizei stride = (
        layout.positionDimensions +
        layout.textureDimensions +
        layout.normalDimensions
    ) * sizeof(GLfloat);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 
        layout.positionDimensions, 
        GL_FLOAT, 
        GL_FALSE, 
        stride, 
        (GLvoid*)0
    );

    if (layout.textureDimensions > 0) {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1, 
            layout.textureDimensions, 
            GL_FLOAT, 
            GL_FALSE, 
            stride, 
            (GLvoid*)(layout.positionDimensions * sizeof(GLfloat))
        );
    }

    if (layout.normalDimensions > 0) {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
            2, 
            layout.normalDimensions, 
            GL_FLOAT, 
            GL_FALSE, 
            stride,
            (GLvoid*)((layout.positionDimensions + layout.textureDimensions) * sizeof(GLfloat))
        );
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data[0], GL_STATIC_DRAW);


    // Vertex Shader
    vsid = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(
        vsid, 
        1,
        &vshaderSource,
        new GLint[1]{(GLint)std::char_traits<char>::length(vshaderSource)}
    );
    glCompileShader(vsid);

    size_t maxLogSize = 1000;
    GLchar infoLog [maxLogSize];
    GLsizei length;

    glGetShaderInfoLog(vsid, maxLogSize, &length, infoLog);
    std::cout << infoLog << std::endl;

    // Fragment Shader
    fsid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(
        fsid, 
        1,
        &fshaderSource,
        new GLint[1]{(GLint)std::char_traits<char>::length(fshaderSource)}
    );
    glCompileShader(fsid);

    glGetShaderInfoLog(fsid, maxLogSize, &length, infoLog);
    std::cout << infoLog << std::endl;

    // Create shader program
    pid = glCreateProgram();
    glAttachShader(pid, vsid);
    glAttachShader(pid, fsid);
    glLinkProgram(pid);

    checkError();
}

void RenderObject::draw(Camera* camera) {
    glUseProgram(pid);
    glBindVertexArray(vao);

    glm::mat4 ident;
    glm::mat4 modelMatrix = 
        glm::translate(ident, pos) * 
        glm::toMat4(quat) * 
        glm::scale(ident, scale);
    glm::mat4 MVP = 
        camera->getProjectionMatrix() * 
        camera->getViewMatrix() * 
        modelMatrix;

    GLuint loc = glGetUniformLocation(pid, "MVP");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(MVP));

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glBindVertexArray(0);
    glUseProgram(0);

    checkError();
}

RenderObject RenderObject::fromOBJ(Wavefront::OBJ o) {
    std::vector<GLfloat> data;
    VertexLayout layout { 3, 2, 3 };
    Wavefront::PointInfo p;

    for (Wavefront::TriangleInfo t : o.f) {
        for (size_t i = 0; i < 3; i++) {
            p = t.points[i];
            // position
            if (p.vIndex < o.v.size()) {
                for (auto x : o.v[p.vIndex])
                    data.push_back(x);
            } else {
                layout.positionDimensions = 0;
            }
            // tex coords
            if (p.vtIndex < o.vt.size()) {
                for (auto x : o.vt[p.vtIndex])
                    data.push_back(x);
            } else {
                layout.textureDimensions = 0;
            }
            // normal
            if (p.vnIndex < o.vn.size()) {
                for (auto x : o.vn[p.vnIndex])
                    data.push_back(x);
            } else {
                layout.normalDimensions = 0;
            }
        }  
    }

    RenderObject ro(data, layout);
    ro.tag = o.o;
    return ro;
}