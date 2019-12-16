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
#include "../utils/Particle.h"

const char* vertShaderFilePath = "shaders/basic.vert";
const char* fragShaderFilePath = "shaders/basic.frag";

const char* textureFilePath = "textureImages/lightgray.png";
const char* textureFilePath2 = "textureImages/green.png";

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

using namespace particlesSimulator;
using namespace graphics;
using namespace math;

int main(void)
{

	Window* window = new Window("Test Window", orig_window_width, orig_window_height);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	PRINT_GL_VERSION(glGetString(GL_VERSION));

	Shader shader(vertShaderFilePath, fragShaderFilePath);

	Texture::enableBlending();
	Texture* texture = new Texture(textureFilePath);
	//Texture* texture2 = new Texture(textureFilePath2);

	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);
	shader.setUniformMat4("pr_matrix", mat4::orthographic(-1280.0f, 1280.0f, -720.0f, 720.0f, -1.0f, 1.0f));

	BatchRenderer2D renderer;

	//std::vector<Renderable2D*> sprites;
	//srand(time(NULL));

	////for (float y = 0; y < 9.0f; y++) {
	////	for (float x = 0; x < 16.0f; x ++) {
	////		//sprites.push_back(new Sprite(x, y, 0.1f, 0.1f, math::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
	////		sprites.push_back(new Sprite(x, y, 0.1f, 0.1f, rand() % 2 == 0 ? texture : texture2));
	////	}
	////}

	//float x, y;
	//for (int i = 0; i < 10; i++) {

	//	x =  (rand() / (RAND_MAX / 2560.0f)) - 1280.0f;
	//	y = (rand() / (RAND_MAX / 1440.0f)) - 720.0f;

	//	int r = rand() % 2;

	//	if (r) {
	//		sprites.push_back(new Sprite(x, y, 100.0f, 100.0f, texture));
	//	}
	//	else {
	//		sprites.push_back(new Sprite(x, y, 100.0f, 100.0f, texture2));
	//	}
	//	
	//}

	srand(time(NULL));

	std::vector<Particle*> particles;
	float x_rend = 1240.0f;
	float y_rend = 680.0f;
	float x, y, xv, yv;
	for (int i = 0; i < numver_of_particles; i++) {

		x = (rand() / (RAND_MAX / (x_rend * 2))) - x_rend;
		y = (rand() / (RAND_MAX / (y_rend * 2))) - y_rend;

		xv = ((rand() / (RAND_MAX / (max_x_velocity * 2))) - max_x_velocity);
		yv = ((rand() / (RAND_MAX / (max_y_velocity * 2))) - max_y_velocity);

		particles.push_back(new Particle(x, y, xv, yv, particle0_radius, 1, texture));
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

		/*for (int i = 0; i < sprites.size(); i++) {
			renderer.submit(sprites[i]);
		}*/

		for (int i = 0; i < particles.size(); i++) {
			particles[i]->updatePosition();
			renderer.submit(particles[i]->getSprite());
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
	//delete texture2;
	delete window;

	return 0;
}

