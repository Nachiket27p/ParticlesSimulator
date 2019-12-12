#include "IOHandler.h"
#include "GLErrorManager.h"
#include "src/graphics/Window.h"
#include "src/math/Math.h"
#include "src/graphics/Shader.h"

#include "src/graphics/buffers/Buffer.h"
#include "src/graphics/buffers/IndexBuffer.h"
#include "src/graphics/buffers/VertexArray.h"

const char* vertShaderFilePath = "src/shaders/basic.vert";
const char* fragShaderFilePath = "src/shaders/basic.frag";

int main(void)
{
    using namespace particlesSimulator;
    
    graphics::Window* window = new graphics::Window("Test Window", 1280, 720);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //// set the version we want to use
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //// report the version of opengl being used
    
    PRINT_GL_VERSION(glGetString(GL_VERSION));

    GLfloat vertices[] =
    {
        0, 0, 0,
        0, 3, 0,
        8, 3, 0,
        8, 0, 0
    };
    GLushort indices[] =
    {
        0, 1, 2, 2, 3, 0
    };

    graphics::VertexArray* vertexArray = new graphics::VertexArray();
    graphics::Buffer* buffer = new graphics::Buffer(vertices, 4 * 3, 3);
    graphics::IndexBuffer* indexBuffer = new graphics::IndexBuffer(indices, 6);

    vertexArray->addBuffer(buffer, 0);

    math::mat4 ortho = math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    graphics::Shader* shader = new graphics::Shader(vertShaderFilePath, fragShaderFilePath);
    shader->enable();
    shader->setUniformMat4("pr_matrix", ortho);
    shader->setUniformMat4("ml_matrix", math::mat4::translate(math::vec3(4,3,0)));

    //shader->setUniform2f("light_pos", math::vec2(4.0f, 1.5f));
    shader->setUniform4f("ufm_color", math::vec4(0.2f, 0.3f, 0.8f, 1.0f));

    while (!window->closed()) {
        window->clear();
        vertexArray->bind();
        indexBuffer->bind();
        shader->setUniformMat4("ml_matrix", math::mat4::translate(math::vec3(6, 4.5, 0)));
        glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_SHORT, 0);
        shader->setUniformMat4("ml_matrix", math::mat4::translate(math::vec3(2, 1.5, 0)));
        glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_SHORT, 0);
        indexBuffer->unbind();
        window->update();
    }

    delete shader;
    delete indexBuffer;
    delete vertexArray;
    delete buffer;
    delete window;

    return 0;
}
