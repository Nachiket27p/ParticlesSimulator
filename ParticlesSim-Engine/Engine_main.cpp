#include "src/graphics/Window.h"
#include "IOHandler.h"

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


    while (!window->Closed()) {
        PRINT_WINDOW_SIZE(window->GetWidth(), window->GetHeight());

        window->Clear();

        // create dirty trinagle
        glBegin(GL_QUADS);
        glVertex2f(-0.09f, -0.16f);
        glVertex2f(-0.09f,  0.16f);
        glVertex2f( 0.09f,  0.16f);
        glVertex2f( 0.09f, -0.16f);
        glEnd();

        window->Update();
    }

    delete window;

    return 0;
}
