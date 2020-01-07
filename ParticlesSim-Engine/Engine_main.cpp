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
#include <map>
#include <algorithm>

// location of vertex shader file
const char* vertShaderFilePath = "shaders/basic.vert";
// location of fragment shader file
const char* fragShaderFilePath = "shaders/basic.frag";

// location of texture files
const char* textureFilePath = "textureImages/lightgray.png";
const char* textureFilePath2 = "textureImages/green.png";

// which gpu to use for rendering
#if NVIDIA
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#elif AMD
extern "C"
{
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

using namespace particlesSimulator;
using namespace graphics;
using namespace math;

/*
This function is responsible for performing the comparision operation when calling the
sort function on the list of particles used in the 'MAP' mode.
*/
bool compareParticles(Particle* a, Particle* b);

int main(void)
{
	// create new window within which to render
	Window* window = new Window("Test Window", orig_window_width, orig_window_height);
	// clear the window abd set color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// print opengl version
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

#if MAP
	int totalParticles = numb_particles_col * numb_particles_row;
	std::vector<Particle*> particles;
	//Particle** particles = (Particle**)malloc((totalParticles) * sizeof(Particle*));

	float widthSpacing = orig_window_width / numb_particles_row;
	float heightSpacing = orig_window_height / numb_particles_col;
	float xv, yv;

	for (float x = particle0_diameter; x < orig_window_width - particle0_diameter; x += widthSpacing) {
		for (float y = particle0_diameter; y < orig_window_height - particle0_diameter; y += heightSpacing) {
			xv = ((rand() / (RAND_MAX / (max_x_velocity * 2))) - max_x_velocity);
			yv = ((rand() / (RAND_MAX / (max_y_velocity * 2))) - max_y_velocity);

			Particle* p = new Particle(x, y, xv, yv, particle0_radius, 1, texture);
			particles.push_back(p);
		}
	}

#elif GRID
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

			int idx = (((int)(x / grid_width) + 1) * ((int)(y / grid_width) + 1)) - 1;
			particleGrid[idx].push_back(p);
			//p->gridIndex = idx;
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

	// Matrix transformation to rotate the image but not necessary for the simulation

	/*
	mat4 mat = mat4::translate(vec3(8, 4.5, 5));
	mat *= mat4::rotate(time.elapsed() * 50.0f, vec3(0, 0, 1));
	mat *= mat4::translate(vec3(-8, -4.5, -5));
	shader.setUniformMat4("ml_matrix", mat);
	*/

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window->closed()) {
		// clear the window
		window->clear();
		// initialize the appropriate properties to start rendering
		renderer.begin();

		// perform collision checks using 'MAP' method
#if MAP
		std::sort(particles.begin(), particles.end(), compareParticles);
		for (int i = 0; i < totalParticles; i++) {
			particles[i]->checkInteractionMk2(particles, i);
			particles[i]->updatePosition();
			renderer.submit(particles[i]->getSprite());
		}

		// perform collsion checks using 'GRID' method
#elif GRID
		for (int i = 0; i < gridSize; i++) {
			for (auto* p : particleGrid[i]) {
				p->checkInteractions(particleGrid[i]);
				p->updatePosition();
				renderer.submit(p->getSprite());
			}
		}

		for (int i = 0; i < gridSize; i++) {
			std::vector<Particle*>& p = particleGrid[i];
			for (int j = 0; j < particleGrid[i].size(); j++) {
				int idx = (((int)(p[j]->getSprite()->getPosition().x / grid_width) + 1) * ((int)(p[j]->getSprite()->getPosition().y / grid_width) + 1)) - 1;
				if (i != idx) {
					particleGrid[idx].push_back(p[j]);
					p[j]->checkInteractions(particleGrid[idx]);
					p.erase(particleGrid[i].begin() + j);
				}
			}
		}
#else
		for (int i = 0; i < particles.size(); i++) {
			particles[i]->checkInteractions(particles);
			particles[i]->updatePosition();
			renderer.submit(particles[i]->getSprite());
		}
#endif
		
		renderer.end();

		// push all the sprites to the gpu and tell it to render them
		renderer.flush();

		// tell the window to update its content
		window->update();

		// fps counter
		frames++;
		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	// delete the texture and window
	delete texture;
	delete window;

	return 0;
}

bool compareParticles(Particle* a, Particle* b)
{
	float aPos = (a->getSprite()->m_position.y) * orig_window_width + a->getSprite()->m_position.x;
	float bPos = (b->getSprite()->m_position.y) * orig_window_width + b->getSprite()->m_position.x;

	if (aPos < bPos) {
		return true;
	}
	else {
		return false;
	}
}
