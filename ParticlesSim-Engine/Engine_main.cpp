#include "IOHandler.h"
#include "GLErrorManager.h"

#include "src/math/Math.h"

#include "src/graphics/Window.h"
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

#include "src/graphics/Texture.h"

#include <time.h>
#include "src/utils/Timer.h"



const char* vertShaderFilePath = "src/shaders/basic.vert";
const char* fragShaderFilePath = "src/shaders/basic.frag";
const char* textureFilePath = "TextureImages/blue.png";
const char* textureFilePath2 = "TextureImages/red.png";

int main(void)
{
	using namespace particlesSimulator;
	using namespace graphics;
	using namespace math;

	Window* window = new Window("Test Window", 1280, 720);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	PRINT_GL_VERSION(glGetString(GL_VERSION));

	Shader shader(vertShaderFilePath, fragShaderFilePath);

	Texture::enableBlending();
	Texture* texture = new Texture(textureFilePath);
	Texture* texture2 = new Texture(textureFilePath2);

	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);
	shader.setUniformMat4("pr_matrix", mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

	BatchRenderer2D renderer;

	std::vector<Renderable2D*> sprites;
	srand(time(NULL));

	//for (float y = 0; y < 9.0f; y++) {
	//	for (float x = 0; x < 16.0f; x ++) {
	//		//sprites.push_back(new Sprite(x, y, 0.1f, 0.1f, math::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
	//		sprites.push_back(new Sprite(x, y, 0.1f, 0.1f, rand() % 2 == 0 ? texture : texture2));
	//	}
	//}

	float x, y;
	for (int i = 0; i < 1000; i++) {

		x =  (rand() / (RAND_MAX / 15.0f)) + 0.5f;
		y = (rand() / (RAND_MAX / 8.0f)) + 0.5f;

		sprites.push_back(new Sprite(x, y, 0.1f, 0.1f, rand() % 2 == 0 ? texture : texture2));
	}

	

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window->closed()) {

		/*mat4 mat = mat4::translate(vec3(8, 4.5, 5));
		mat *= mat4::rotate(time.elapsed() * 50.0f, vec3(0, 0, 1));
		mat *= mat4::translate(vec3(-8, -4.5, -5));
		shader.setUniformMat4("ml_matrix", mat);*/

		window->clear();

		renderer.begin();

		for (int i = 0; i < sprites.size(); i++) {
			renderer.submit(sprites[i]);
		}

		renderer.end();

		renderer.flush();

		window->update();
		frames++;

		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	delete texture;
	delete texture2;
	delete window;

	return 0;
}
