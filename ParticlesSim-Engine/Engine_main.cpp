#include "IOHandler.h"
#include "GLErrorManager.h"
#include "src/graphics/Window.h"
#include "src/math/Math.h"
#include "src/graphics/Shader.h"

#include "src/graphics/buffers/Buffer.h"
#include "src/graphics/buffers/IndexBuffer.h"
#include "src/graphics/buffers/VertexArray.h"

#include "src/graphics/Renderer2D.h"
#include "src/graphics/Renderable2D.h"
#include "src/graphics/Simple2DRenderer.h"

const char* vertShaderFilePath = "src/shaders/basic.vert";
const char* fragShaderFilePath = "src/shaders/basic.frag";

int main(void)
{
    using namespace particlesSimulator;
    using namespace graphics;
    using namespace math;
    
    Window* window = new Window("Test Window", 1280, 720);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    PRINT_GL_VERSION(glGetString(GL_VERSION));

    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
    Shader shader(vertShaderFilePath, fragShaderFilePath);
    shader.enable();
    shader.setUniformMat4("pr_matrix", ortho);
    shader.setUniformMat4("ml_matrix", mat4::translate(vec3(4,3,0)));

    Renderable2D sprite(math::vec3(5, 5, 0), math::vec2(4, 4), math::vec4(1, 0, 1, 1), shader);
    Renderable2D sprite2(math::vec3(7, 1, 0), math::vec2(2, 2), math::vec4(0, 1, 0, 1), shader);

    Simple2DRenderer renderer;

    shader.setUniform4f("ufm_color", vec4(0.2f, 0.3f, 0.8f, 1.0f));

    while (!window->closed()) {
        window->clear();
        
        renderer.submit(&sprite);

        renderer.submit(&sprite2);
        renderer.flush();
        
        window->update();
    }

    delete window;

    return 0;
}
