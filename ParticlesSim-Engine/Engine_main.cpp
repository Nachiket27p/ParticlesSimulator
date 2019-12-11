#include "IOHandler.h"
#include "src/graphics/Window.h"
#include "src/math/Math.h"

int main(void)
{
    using namespace particlesSimulator;
    
    graphics::Window* window = new graphics::Window("Test Window", 1280, 720);

    // set the version we want to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // set plain color for window
    glClearColor(0.2f, 0.2f, 0.9f, 1.0f);

    // report the version of opengl being used
    PRINT_GL_VERSION(glGetString(GL_VERSION));

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    math::mat4 pos = math::mat4::translation(math::vec3(2, 3, 4));
    pos *= math::mat4::identity();

    while (!window->closed()) {
        window->clear();

        //// create dirty trinagle
        //glBegin(GL_QUADS);
        //glVertex2f(-0.09f, -0.16f);
        //glVertex2f(-0.09f,  0.16f);
        //glVertex2f( 0.09f,  0.16f);
        //glVertex2f( 0.09f, -0.16f);
        //glEnd();

        glDrawArrays(GL_ARRAY_BUFFER, 0, 0);

        window->update();
    }

    delete window;

    return 0;
}
