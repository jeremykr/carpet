#include "RenderObject.h"

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

    std::cout << vertexCount << std::endl;
    // Define shader sources
    const GLchar* vshaderSource = R"glsl(
    # version 330 core
    layout(location = 0) in vec3 pos;
    uniform mat4 MVP;
    void main() {
        gl_Position = MVP * vec4(pos, 1.0);
    })glsl";

    const GLchar* fshaderSource = R"glsl(
    # version 330 core
    out vec4 color;
    void main() {
        color = vec4(1,1,1,1);
    })glsl";

    // Setup vertex buffers
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
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

    GLchar infoLog [100];
    GLsizei length;

    glGetShaderInfoLog(vsid, 100, &length, infoLog);
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

    glGetShaderInfoLog(fsid, 100, &length, infoLog);
    std::cout << infoLog << std::endl;

    // Create shader program
    pid = glCreateProgram();
    glAttachShader(pid, vsid);
    glAttachShader(pid, fsid);
    glLinkProgram(pid);

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
}

RenderObject RenderObject::fromOBJ(OBJ::OBJ o) {
    std::vector<GLfloat> data;
    VertexLayout layout;

    // TODO: Implement

    return RenderObject(data, layout);
}