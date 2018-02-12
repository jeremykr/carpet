#include "Triangle.h"

Triangle::Triangle() {
    // Define vertex data
    GLfloat vbuf [9] = {
        -1., -1., 0.,
        1., -1., 0.,
        0., 1., 0.
    };

    // Define shader sources
    const GLchar* vShaderSource = R"glsl(
    # version 330 core
    layout(location = 0) in vec3 pos;
    void main() {
        gl_Position = vec4(pos, 1.0);
    })glsl";

    const GLchar* fShaderSource = R"glsl(
    # version 330 core
    out vec4 color;
    void main() {
        color = vec4(1,1,1,1);
    })glsl";

    // Setup vertex buffers
    GLsizeiptr vbufSize = sizeof(GLfloat) * 9;
    GLuint vao, vsid, fsid;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vbufSize, &vbuf, GL_STATIC_DRAW);

    // Vertex Shader
    vsid = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(
        vsid, 
        1,
        &vShaderSource,
        new GLint[1]{(GLint)std::char_traits<char>::length(vShaderSource)}
    );
    glCompileShader(vsid);

    // Fragment Shader
    fsid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(
        fsid, 
        1,
        &fShaderSource,
        new GLint[1]{(GLint)std::char_traits<char>::length(fShaderSource)}
    );
    glCompileShader(fsid);

    // Create shader program
    pid = glCreateProgram();
    glAttachShader(pid, vsid);
    glAttachShader(pid, fsid);
}

void Triangle::draw() {
    glUseProgram(pid);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}