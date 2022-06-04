#pragma once

namespace particlesSimulator {
	
	// If set appropriate macro based on your gpu
	// Both can be set to 0 to use integrated graphics

	#define NVIDIA
	
	//#define AMD

	// set value to either 1 or 0.
	// This defines which method to use when performing collision checks, the 'MAP' method
	// maps the 2d position of the particle (x, y) coordinates onto a 1d line using the
	// same method as 2d arrays are stored in memory, row major ordering. Then the particles
	// are sorted such that particles closes to each other are next to each other in the 1d line
	// after sorting. Unfortunately atleast 2*(max number of particles in a single row) have to be
	// checked to ensure not interactions are missed. As a result this method is lower for small
	// particle sizes because is the canvas is wide enough and the particles are small enough. You
	// potentially have a situation whre all particles are checked. Although this can be faster if the
	// size of the particle is large enough relative to the width of the canvas.
	
	//#define MAP

	// This method is faster than the 'MAP' method, it puts an imaginary grid over the rendering space
	// by creating a 2d array in which it stores the particles, based on their (x, y) positon. The 2d arrays
	// is represented as a 1d array using row major ordering. The grid reduces the number of particles a specific
	// particle needs to check because it can only collide with particles in the block its in and the 8 that surround it

	#define GRID

	// This enabled Multithreading to significantly improve performance as the main bottleneck is the CPU computation not the GPU rendering.

	 #define MT

	// !!! IMPORTANT !!!
	// If both 'MAP' and 'GRID' are defined to 0 than the primitive method which checks each particle with every
	// other particle will be used. Not recommended its vvvvvvveeeeeeeeeeeeerrrrrrrrrrrrrryyyyyyyyyyy slow with higher particle count (more than 5000).
	// If both 'MAP' and 'GRID' are defined to 1 than 'MAP' method will be used.

	// Enable or disable vertical sync.
	// NOTE! diabling vertical sync can have unusual behavior due to the position update frequency of the particles being 60 Hz.
	
	// #define VSYNC

	// Set the width and height of the window in which to render
	// The window is resizable after starting the progrm but everything will scale with the window size
	static const int orig_window_width = 3200;
	static const int orig_window_height = 1400;

	// Define the number of particles per row and column.
	// NOTE! if the numer of particles is larger than 'width or height of window'/'diameter of particle' than particles will render
	// inside each other and undefined behavior is expected breaks.
	static const int numb_particles_row = 300;
	static const int numb_particles_col = 200;

	// Set the radius of the particle
	static const float particle0_radius = 2.0f;
	static const float particle0_diameter = 2.0f * particle0_radius;
	static const float particle0_diameter_Sqrd = particle0_diameter * particle0_diameter;

	// Set the max MAGNITURE of the x and y velocity of the particles.
	static const float max_x_velocity = 10.0f;
	static const float max_y_velocity = 10.0f;

	// The size of the imaginary grid if using the 'GRID' mode of collision detection.
	static const int grid_width = 120;

	static const int grid_size = (((orig_window_width - (int)(2 * particle0_diameter)) / grid_width) + 1) * (((orig_window_height - (int)(2 * particle0_diameter)) / grid_width) + 1);

	static const int desired_worker_threads = 8;
	static const int worker_load = grid_size / desired_worker_threads;
	static const int worker_count = grid_size / worker_load;

	// Number of columns and rows
	static const int numCols = (int)(orig_window_width / grid_width);
	static const int numRows = (int)(orig_window_height / grid_width);

	// set the update interval, this also affects the speed at which the simulation will run.
	const float t_interval = 1.0f / 60.0f;
}
