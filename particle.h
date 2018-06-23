#ifndef PARTICLE_H
#define PARTICLE_H


#include <math.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

typedef struct particle{
  int x;
  int y;
  int dest_x;
  int dest_y;
}particle;

void init_particles(particle *particle_array, int elements, int x, int y, int w, int h);
void init_sphere(particle *particle_array, int elements, int x, int y, int r);

void move_particles(particle *particle_array, int elements, int x, int y);

void render_jet_flame(particle *particle_array, int elements, int x, int y, int w, int h, int speed);
void render_falling_particles(particle *particle_array, int elements, int x, int y, int w, int h, int speed);
void render_sphere(particle *particle_array, int elements, int x, int y, int r, int speed);

void blit_particles(SDL_Surface *screen, particle *particle_array, int elements, unsigned char r, unsigned char g, unsigned char b);

#endif