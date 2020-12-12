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
void inline resetParticleEdgeList(std::vector<std::vector<Particle*>>& particlesOnEdge);
void inline computeParticleEdgeList(std::vector<Particle*>& p, std::vector<std::vector<Particle*>>& particlesOnEdge, int j, int col, int row, float px, float py);

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

	std::vector<std::vector<Particle*>> particleGrid(grid_size);
	std::vector<std::vector<Particle*>> particlesOnEdge(grid_size);
	for (int i = 0; i < grid_size; i++) {
		particleGrid[i] = std::vector<Particle*>();
		particlesOnEdge[i] = std::vector<Particle*>();
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

	//float x = 50;
	//float y = 50;
	//int col = (int)(x / grid_width);
	//int row = (int)(y / grid_width);
	//int idx = (col + (row*numCols));
	//Particle* tp1 = new Particle(50, 50, 10, 10, particle0_radius, 1, texture);
	//particleGrid[idx].push_back(tp1);

	//x = 50;
	//y = 100;
	//col = (int)(x / grid_width);
	//row = (int)(y / grid_width);
	//idx = (col + (row *numCols));
	//Particle* tp2 = new Particle(100, 100, -10, -10, particle0_radius, 1, texture);
	//particleGrid[idx].push_back(tp2);

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

	//particles.push_back(new Particle(100, 100, 5, 5, particle0_radius, 1, texture));
	//particles.push_back(new Particle(200, 200, -5, -5, particle0_radius, 1, texture));

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
		}

		for (auto* p : particles) {
			p->resetInteractedWith();
			p->updatePosition();
			renderer.submit(p->getSprite());
		}

		// perform collsion checks using 'GRID' method
#elif GRID
		for (int i = 0; i < grid_size; i++) {
			for (auto* p : particleGrid[i]) {
				p->checkInteractions(particleGrid[i], particlesOnEdge[i]);
			}
		}

		// Calculate the new positions of the particles after all the velocities have been updated
		// After calculating the new position submit the particle for rendering
		for (int i = 0; i < grid_size; i++) {
			for (auto* p : particleGrid[i]) {
				p->resetInteractedWith();
				p->updatePosition();
				renderer.submit(p->getSprite());
			}
		}
		
		// clear the list of list of particles crossing over the imaginary grid lines
		resetParticleEdgeList(particlesOnEdge);
		for (int i = 0; i < grid_size; i++) {
			std::vector<Particle*>& p = particleGrid[i];
			for (int j = 0; j < particleGrid[i].size(); j++) {
				float px = p[j]->getSprite()->getPosition().x;
				float py = p[j]->getSprite()->getPosition().y;
				int col = (int)(px / grid_width);
				int row = (int)(py / grid_width);
				int idx = (col + (row * numCols));
				
				// check if the particle lies on the grid
				computeParticleEdgeList(p, particlesOnEdge, j, col, row, px, py);

				// check if the particle has move to a different grid slot
				if (i != idx) {
					particleGrid[idx].push_back(p[j]);
					p.erase(particleGrid[i].begin() + j);
				}

			}
		}
		
		//std::cout << testParticle->getSprite()->getPosition().x << ", " << testParticle->getSprite()->getPosition().y << std::endl;
#else
		// update the velocity based on any interactions
		for (int i = 0; i < particles.size(); i++) {
			particles[i]->checkInteractions(particles);
		}

		for (int i = 0; i < particles.size(); i++) {
			particles[i]->resetInteractedWith();
		}

		// update the position and submit to renderer
		for (int i = 0; i < particles.size(); i++) {
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

void inline resetParticleEdgeList(std::vector<std::vector<Particle*>>& particlesOnEdge)
{
	// clear all the vectors which hold the particles which lie on the edge of a grid
	for (int i = 0; i < particlesOnEdge.size(); i++)
		particlesOnEdge[i].clear();
}

void inline computeParticleEdgeList(std::vector<Particle*>& p, std::vector<std::vector<Particle*>>& particlesOnEdge, int j, int col, int row, float px, float py)
{
	// get the size of the particle
	math::vec2 particleSize = p[j]->getSprite()->getSize();
	float pW = particleSize[0];
	
	float leftX = px - (col * grid_width);
	float rightX = ((col+1) * grid_width) - px;
	float bottomY = py - (row * grid_width);
	float topY = ((row+1) * grid_width) - py;
	int diag = 0;

	// Shows how each grid boundary is viewed
	//
	//	12		  4			6
	//		-------------
	//		|			|
	//	  8	|			| 2
	//		|			|
	//		-------------
	//	7		  1			3
	//

	// check if the particle overlaps with left or right boundries
	if (((col-1) >= 0) && (leftX <= 0.0f)) {
		diag += 8;
		//(col + (row * numCols));
		int edgeIdx = (col - 1) + (row*numCols);
		particlesOnEdge[edgeIdx].push_back(p[j]);
	}
	else if (((col+1) < numCols) && (rightX <= pW)) {
		diag += 2;
		int edgeIdx = (col + 1) + (row * numCols);
		particlesOnEdge[edgeIdx].push_back(p[j]);
	}

	// check if the particle overlaps with top and bottom boundries
	if (((row-1) >= 0) && (bottomY <= 0.0f)) {
		diag += 1;
		int edgeIdx = col + ((row - 1)*numCols);
		particlesOnEdge[edgeIdx].push_back(p[j]);
	}
	else if (((row + 1) < numRows) && (topY <= pW)) {
		diag += 4;
		int edgeIdx = col + ((row + 1) * numCols);
		particlesOnEdge[edgeIdx].push_back(p[j]);
	}

	// check using diag if the particle is diagonally corssing tow boundries
	// 3 == the particle is crossing the bottom right corner
	// 6 == the particle is crossing the top right corner
	// 12 == the particle is crossing the top left corner
	// 7 == the particle is crossing the bottom left
	if (diag) {
		if (diag == 3) { // Bottom right corner
			int edgeIdx = (col + 1) + ((row-1)*numCols);
			particlesOnEdge[edgeIdx].push_back(p[j]);
		}
		else if (diag == 6) { // Top right corner
			int edgeIdx = (col + 1) + ((row + 1)*numCols);
			particlesOnEdge[edgeIdx].push_back(p[j]);
		}
		else if (diag == 12) { // Top left corner
			int edgeIdx = (col - 1) + ((row + 1)*numCols);
			particlesOnEdge[edgeIdx].push_back(p[j]);
		}
		else if (diag == 7) { // Bottom left corner
			int edgeIdx = (col - 1) + ((row - 1)*numCols);
			particlesOnEdge[edgeIdx].push_back(p[j]);
		}
	}
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
