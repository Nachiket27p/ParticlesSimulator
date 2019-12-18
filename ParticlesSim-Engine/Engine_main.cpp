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

#define GRID 0

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

	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);
	shader.setUniformMat4("pr_matrix", mat4::orthographic(0, orig_window_width, 0, orig_window_height, -1.0f, 1.0f));

	BatchRenderer2D renderer;

	srand(time(NULL));


	int gridRows = (int)(orig_window_height / grid_width);
	int gridCols = (int)(orig_window_width / grid_width);
	int gridSize = gridRows * gridCols;

#if GRID

	//INCOMPLETE
	std::vector<Particle*> particles;

	float xv, yv;

	float widthSpacing = orig_window_width / numb_particles_row;
	float heightSpacing = orig_window_height / numb_particles_col;

	std::vector<std::vector<Particle*>> particleGrid(gridSize);
	for (int i = 0; i < gridSize; i++) {
		particleGrid[i] = std::vector<Particle*>();
	}

	for (float x = particle0_diameter; x < orig_window_width - particle0_diameter; x += widthSpacing) {
		for (float y = particle0_diameter; y < orig_window_height - particle0_diameter; y += heightSpacing) {
			xv = ((rand() / (RAND_MAX / (max_x_velocity * 2))) - max_x_velocity);
			yv = ((rand() / (RAND_MAX / (max_y_velocity * 2))) - max_y_velocity);

			Particle* p = new Particle(x, y, xv, yv, particle0_radius, 1, texture);
			particles.push_back(p);

			int idx = (((int)(x / grid_width) + 1) * ((int)(y / grid_width) + 1)) - 1;
			particleGrid[idx].push_back(p);
		}
	}

#else
	std::vector<Particle*> particles;

	float xv, yv;

	float widthSpacing = orig_window_width / numb_particles_row;
	float heightSpacing = orig_window_height / numb_particles_col;

	for (float x = particle0_diameter; x < orig_window_width - particle0_diameter; x += widthSpacing) {
		for (float y = particle0_diameter; y < orig_window_height - particle0_diameter; y += heightSpacing) {
			xv = ((rand() / (RAND_MAX / (max_x_velocity * 2))) - max_x_velocity);
			yv = ((rand() / (RAND_MAX / (max_y_velocity * 2))) - max_y_velocity);

			particles.push_back(new Particle(x, y, xv, yv, particle0_radius, 1, texture));
		}
	}

#endif
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

#if GRID
		// INCOMPLETE
		for (int i = 0; i < gridSize; i++) {
			for (auto* p : particleGrid[i]) {
				p->updatePosition(particleGrid[i]);
				renderer.submit(p->getSprite());
			}
		}

#else
		for (int i = 0; i < particles.size(); i++) {
			particles[i]->updatePosition(particles);
			renderer.submit(particles[i]->getSprite());
		}
#endif

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

