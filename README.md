# Particle Simulation using OpenGL

## Info
* This particle simulator uses OpenGL libraries to render the particles and the CPU is used to perform the physics calculations. This simulator can be configured from the InitializationData.h file. The simulator consists of multiple methos of computing the interactions. The most basic is the brute force every perticle is compared to every other particle, this was only used to ensure the physics was correct. The other methods are 'GRID' and 'MAP' more details about these can be seen below.

## Hardware/Softare used to test
* Dell xps 9560
* i7-7700HQ
* 16GB ram
* GTX 1050 - 4GB
* Windows 10

## Interaction Methods
* **Brute Force**
  * This is the simplest and slowest method which compares every particle with every other particle.
  * On the system specified specifies above any more than 1000 particles causes really slow performance.

* **GRID Method**
  * This methid is the balance between performance and flexibility.
  * To expand on the statement above because the canvas is split into a virtual grid it only needs to check interactions between particles in the grid.
  * This method is flexible because there there is no specific relation between the particle size and the canvas size which affects the performance like the MAP method.
  * This method can handel up to 40,000 particles at 60fps.
  * Visualization of the grid method.

                                                    |         |
                                            o o o o | o o o o | o o o o
                                            o o o o | o o o o | o o o o
                                            o o o o | o o o o | o o o o
                                        ------------|---------|-----------
                                            o o o o | o o o o | o o o o
                                            o o o o | o o o o | o o o o
                                            o o o o | o o o o | o o o o
                                        ------------|---------|-----------
                                            o o o o | o o o o | o o o o
                                            o o o o | o o o o | o o o o
                                            o o o o | o o o o | o o o o
                                                    |         |
* **MAP Method**
  * This method is a little more complicated to extract the most performance out of.
  * To understand this method understand that all the particles can be mapped from 2d coordinates to 1d coordinates and sorting theme places them in the correct ordering.
  * This allows this method to only check X amount left on the 1d line and X amount right on the 1d line.
  * 2X = (width of grid / diameter of particle) * 3
    * A visualizations, let k denote the particle being checked. and the 'o' be the other particles. The maximum particles we need to check is indicated by the arrows, the number of particles is three rows completely full of particles.
            
                                                . . . . . . . . . . .
                                                . . . . . . . . . . .
                                    ------->    o o o o o o o o o o o
                                    ------->    o o o o o k o o o o o
                                    ------->    o o o o o o o o o o o
                                                . . . . . . . . . . .
                                                . . . . . . . . . . .
                                                . . . . . . . . . . .

  * This method can vary on performance based the size of the particle and the width of the canvas. The less particles which can fit in a row along the width of the grid the less particles this method has to check so the better the performance. So for a narrow width and a large particle size yields better performance than the GRID method. Alternatively if the density of particles is sparse and the width is large than this method in the limit will eventualy change into the brute force method because it will check every particle.

## Usage instructions
* Examples of how to set parameter is shown below.

        If set appropriate macro based on your gpu
            Both can be set to 0 to use integrated graphics
            #define NVIDIA 1
            #define AMD 0

        set value to either 1 or 0.
        This defines which method to use when performing collision checks, the 'MAP' method
        maps the 2d position of the particle (x, y) coordinates onto a 1d line using the
        same method as 2d arrays are stored in memory, row major ordering. Then the particles
        are sorted such that particles closes to each other are next to each other in the 1d line
        after sorting. Unfortunately atleast 2*(max number of particles in a single row) have to be
        checked to ensure not interactions are missed. As a result this method is lower for small
        particle sizes because is the canvas is wide enough and the particles are small enough. You
        potentially have a situation whre all particles are checked. Although this can be faster if the
        size of the particle is large enough relative to the width of the canvas.
            #define MAP 0

        Set this value to 1 if you wish to use the grid method and remember to set MAP to 0.
            #define GRID 1

        !!! IMPORTANT !!!
        If both 'MAP' and 'GRID' are defined to 0 than the primitive method which checks each particle with every
        other particle will be used. Not recommended its vvvvvvveeeeeeeeeeeeerrrrrrrrrrrrrryyyyyyyyyyy slow with higher particle count (more than 5000).
        If both 'MAP' and 'GRID' are defined to 1 than 'MAP' method will be used.

        Enable or disable vertical sync.
        NOTE! diabling vertical sync can have unusual behavior due to the position update frequency of the particles being 60 Hz.
            #define VSYNC 1

        Set the width and height of the window in which to render
        The window is resizable after starting the progrm but everything will scale with the window size
            static const int orig_window_width = 2000;
            static const int orig_window_height = 2000;

        Define the number of particles per row and column.
        NOTE! if the numer of particles is larger than 'width or height of window'/'diameter of particle' than particles will render
        inside each other and undefined behavior is expected breaks.
            static const int numb_particles_row = 40;
            static const int numb_particles_col = 40;

        Set the radius of the particle
            static const float particle0_radius = 5.0f;
            static const float particle0_diameter = 2.0f * particle0_radius;
            static const float particle0_diameter_Sqrd = particle0_diameter * particle0_diameter;

        Set the max MAGNITURE of the x and y velocity of the particles.
            static const float max_x_velocity = 20.0f;
            static const float max_y_velocity = 20.0f;

        The size of the imaginary grid if using the 'GRID' mode of collision detection.
            static const int grid_width = 100;

        Do not touch this unless you have understood how the grid method works
            static const int grid_size = (((orig_window_width - (int)(2* particle0_diameter)) / grid_width) + 1) * (((orig_window_height - (int)(2 * particle0_diameter)) / grid_width) + 1);

        Number of columns and rows
            static const int numCols = (int)(orig_window_width / grid_width);
            static const int numRows = (int)(orig_window_height / grid_width);

        set the update interval, this also affects the speed at which the simulation will run.
            const float t_interval = 1.0f / 60.0f;
