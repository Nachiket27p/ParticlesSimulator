#include "IOHandler.h"
#include "GLErrorManager.h"
#include "src/graphics/Window.h"
#include "src/math/Math.h"
#include "src/graphics/Shader.h"

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

    GLfloat vertices[] = {  0, 0, 0,
                            8, 0, 0,
                            0, 3, 0,
                            0, 3, 0,
                            8, 3, 0,
                            8, 0, 0, };
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);
    glEnableVertexAttribArray(0);

    math::mat4 ortho = math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    graphics::Shader* shader = new graphics::Shader(vertShaderFilePath, fragShaderFilePath);
    shader->enable();
    shader->setUniformMat4("pr_matrix", ortho);
    shader->setUniformMat4("ml_matrix", math::mat4::translate(math::vec3(4,3,0)));
    shader->setUniform2f("light_pos", math::vec2(4.0f, 1.5f));
    shader->setUniform4f("ufm_color", math::vec4(0.2f, 0.3f, 0.8f, 1.0f));

    while (!window->closed()) {
        window->clear();

        glDrawArrays(GL_TRIANGLES, 0, 6);

        window->update();
    }

    delete shader;

    delete window;

    return 0;
}
