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
#include "src/graphics/BatchRenderer2D.h"

#include "src/graphics/StaticSprite.h"
#include "src/graphics/Sprite.h"

#include <time.h>
#include "src/utils/Timer.h"

#define BATCH_RENDERER 1

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

	std::vector<Renderable2D*> sprites;
	srand(time(NULL));

	for (float y = 0; y < 9.0f; y += 0.05) {
		for (float x = 0; x < 16.0f; x += 0.05) {
#if BATCH_RENDERER
			sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, math::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
#else
			sprites.push_back(new StaticSprite(x, y, 0.04f, 0.04f, math::vec4(rand() % 1000 / 1000.0f, 0, 1, 1), shader));
#endif
		}
	}

#if BATCH_RENDERER
	Sprite sprite(5, 5, 4, 4, math::vec4(1, 0, 1, 1));
	Sprite sprite2(7, 1, 2, 2, math::vec4(0, 1, 0, 1));
	BatchRenderer2D renderer;
#else
	StaticSprite sprite(5, 5, 4, 4, math::vec4(1, 0, 1, 1), shader);
	StaticSprite sprite2(7, 1, 2, 2, math::vec4(0, 1, 0, 1), shader);
	Simple2DRenderer renderer;
#endif
	shader.setUniform4f("ufm_color", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window->closed()) {

		mat4 mat = mat4::translate(vec3(8, 4.5, 5));
		mat *= mat4::rotate(time.elapsed() * 50.0f, vec3(0, 0, 1));
		mat *= mat4::translate(vec3(-8, -4.5, -5));
		shader.setUniformMat4("ml_matrix", mat);

		window->clear();

#if BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i++) {
			renderer.submit(sprites[i]);
		}

#if BATCH_RENDERER
		renderer.end();
#endif
		renderer.flush();

		window->update();
		frames++;

		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	delete window;

	return 0;
}
