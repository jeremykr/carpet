#include "TestTriangle.h"
#include <iostream>

TestTriangle::TestTriangle() {
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
    uniform mat4 MVP;
    void main() {
        gl_Position = MVP * vec4(pos, 1.0);
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

    GLchar infoLog [100];
    GLsizei length;

    glGetShaderInfoLog(vsid, 100, &length, infoLog);
    std::cout << infoLog << std::endl;

    // Fragment Shader
    fsid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(
        fsid, 
        1,
        &fShaderSource,
        new GLint[1]{(GLint)std::char_traits<char>::length(fShaderSource)}
    );
    glCompileShader(fsid);

    glGetShaderInfoLog(fsid, 100, &length, infoLog);
    std::cout << infoLog << std::endl;

    // Create shader program
    pid = glCreateProgram();
    glAttachShader(pid, vsid);
    glAttachShader(pid, fsid);
    glLinkProgram(pid);
}

void TestTriangle::draw(Camera* camera) {
    glUseProgram(pid);

    glm::mat4 ident;
    glm::mat4 modelMatrix = glm::translate(ident, pos) * glm::scale(ident, scale);
    glm::mat4 MVP = camera->getProjectionMatrix() * camera->getViewMatrix() * modelMatrix;

    GLuint loc = glGetUniformLocation(pid, "MVP");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(MVP));

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}