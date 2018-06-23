![preview.gif](https://raw.github.com/AlxHnr/rocket_flight/master/preview.gif)
![jetflame.gif](https://raw.github.com/AlxHnr/rocket_flight/master/jetflame.gif)

The rocket will follow your mouse. Press any mouse button to respawn the
particles in the sphere with random colors. The particle count can be
increased in
[main.c](https://github.com/AlxHnr/rocket_flight/blob/master/main.c). This
simulation is single-threaded.

## Building

This program requires the development files of the following libraries:

* SDL (_not_ SDL2)
* SDL\_gfx

Build and run the game using only one thread: `make -j1 run`.
