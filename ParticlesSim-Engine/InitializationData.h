#pragma once

namespace particlesSimulator {
	
	// If set appropriate macro based on your gpu
	// Both can be set to 0 to use integrated graphics
	#define NVIDIA 1
	#define AMD 0

	// This defines which method to use when performing collision checks, the 'MAP' method
	// maps the 2d position of the particle (x, y) coordinates onto a 1d line using the
	// same method as 2d arrays are stored in memory, row major ordering. Then the particles
	// are sorted such that particles closes to each other are next to each other in the 1d line
	// after sorting. This drastically reduces the amount of computation required to simulate collisions. 
	// This is the faster of the two methods, because the particles are sorted they only need to
	// check a few particles before and after in the list.
	// set value to either 1 or 0.
	#define MAP 1

	// This method is slowr than the 'MAP' method, it puts an imaginary grid over the rendering space
	// by creating a 2d array in which it stores the particles, based on their (x, y) positon. The 2d arrays
	// is represented as a 1d array using row major ordering. The grid reduces the number of particles a specific
	// particle needs to check because it can only collide with particles in the block its in and the 8 that surround it
	#define GRID 0

	// !!! IMPORTANT !!!
	// If both 'MAP' and 'GRID' are defined to 0 than the primitive method which checks each particle with every
	// other particle will be used. Not recommended its vvvvvvveeeeeeeeeeeeerrrrrrrrrrrrrryyyyyyyyyyy slow with higher particle count (more than 5000).
	// If both 'MAP' and 'GRID' are defined to 1 than 'MAP' method will be used.

	// Enable or disable vertical sync.
	// NOTE! diabling vertical sync can have unusual behavior due to the position update frequency of the particles being 60 Hz.
	#define VSYNC 1

	// Set the width and height of the window in which to render
	// The window is resizable after starting the progrm but everything will scale with the window size
	static const int orig_window_width = 1600;
	static const int orig_window_height = 1600;

	// Define the number of particles per row and column.
	// NOTE! if the numer of particles is larger than 'width or height of window'/'diameter of particle' than particles will render
	// inside each other and undefined behavior is expected breaks.
	static const int numb_particles_row = 20;
	static const int numb_particles_col = 20;

	// Set the radius of the particle
	static const float particle0_radius = 5.0f;
	static const float particle0_diameter = 2.0f * particle0_radius;
	static const float particle0_diameter_Sqrd = particle0_diameter * particle0_diameter;

	// Set the max MAGNITURE of the x and y velocity of the particles.
	static const float max_x_velocity = 50.0f;
	static const float max_y_velocity = 50.0f;

	// The size of the imaginary grid if using the 'GRID' mode of collision detection.
	static const float grid_width = 100;

	// set the update interval, this also affects the speed at which the simulation will run.
	const float t_interval = 1.0f / 60.0f;
}
