#include <SDL.h>
#include <particle.h>
#include <render_gfx.h>

#define game_speed 15

//rocket defines
#define rocket_size 10
#define rocket_speed 1
#define rocket_color 255, 50, 0
#define jet_flame_h 60

//particle defines
#define lower_particles 7000
#define mid_particles 3500
#define upper_particles 2500

#define lower_particle_color 255, 0, 0
#define mid_particle_color 255, 150, 0
#define upper_particle_color 255, 255, 0

#define star_amount 5000

//sphere defines
#define sphere_r 325
#define sphere_particles 50000
#define sphere_speed 1

#ifdef __WIN32__
  int WinMain(int argc, char *argv[])
#else
  int main(int argc, char *argv[])
#endif
{
  //variables
  SDL_Surface *screen = NULL;
  SDL_Event user_input;
  
  Uint32 time_stop;
  
  int rocket_x = 0;
  
  particle lower_flame[lower_particles];
  particle mid_flame[mid_particles];
  particle upper_flame[upper_particles];
  
  particle sphere[sphere_particles];
  SDL_Color sphere_color = {255, 255, 255};
  
  particle stars[star_amount];
  
  //init SDL start
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    exit(-1);
  
  SDL_WM_SetCaption("Rocket Flight", NULL);
  
  if((screen = SDL_SetVideoMode(650, 650, 16, SDL_HWSURFACE)) == NULL)
    exit(-1);
  atexit(SDL_Quit);
  SDL_ShowCursor(0);
  //init SDL end
  
  //init particles
  init_particles(sphere, sphere_particles, (Sint16)(screen->w/2) - sphere_r, (Sint16)(screen->h/2) - sphere_r, sphere_r * 2, sphere_r * 2);
  
  init_particles(lower_flame, lower_particles, rocket_x, screen->h - jet_flame_h, rocket_size*4, jet_flame_h);
  init_particles(mid_flame, mid_particles, rocket_x, screen->h - jet_flame_h, rocket_size*4, jet_flame_h);
  init_particles(upper_flame, upper_particles, rocket_x, screen->h - jet_flame_h, rocket_size*4, jet_flame_h);
  
  init_particles(stars, star_amount, 0, 0, screen->w, screen->h);
  
  //main loop start
  time_stop = SDL_GetTicks();
  while(user_input.type != SDL_QUIT)
  {
    //read in user_input
    while(SDL_PollEvent(&user_input))
    {
      if(user_input.type == SDL_MOUSEMOTION && user_input.motion.x > 0 && user_input.motion.x <= screen->w - rocket_size*4)
      {
        rocket_x = user_input.motion.x;
      }
      if(user_input.type == SDL_MOUSEBUTTONDOWN)
      {
        sphere_color.r = rand() % 255 + 1;
        sphere_color.g = rand() % 255 + 1;
        sphere_color.b = rand() % 255 + 1;
        init_particles(sphere, sphere_particles, (Sint16)(screen->w/2) - sphere_r + rand() % sphere_r * 2, (Sint16)(screen->h/2) - sphere_r + rand() % sphere_r * 2, 0, 0);
        time_stop = SDL_GetTicks();
      }
    }
    
    //clean screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    
    //calc gfx
    while(SDL_GetTicks() - time_stop > game_speed)
    {
      //move everithing 1 step
      render_falling_particles(stars, star_amount, 0, 0, screen->w, screen->h, rocket_speed);
      
      render_sphere(sphere, sphere_particles, (Sint16)(screen->w/2), (Sint16)(screen->h/2), sphere_r, sphere_speed);
      
      render_jet_flame(lower_flame, lower_particles, rocket_x, screen->h - jet_flame_h, rocket_size*4, jet_flame_h, rocket_speed);
      render_jet_flame(mid_flame, mid_particles, rocket_x, screen->h - jet_flame_h, rocket_size*4, jet_flame_h, rocket_speed);
      render_jet_flame(upper_flame, upper_particles, rocket_x, screen->h - jet_flame_h, rocket_size*4, jet_flame_h, rocket_speed);
      
      time_stop += game_speed;
    }
    
    //draw gfx
    blit_particles(screen, stars, star_amount, 200, 200, 200);
    
    blit_particles(screen, sphere, sphere_particles, sphere_color.r, sphere_color.g, sphere_color.b);
    
    blit_particles(screen, lower_flame, lower_particles, lower_particle_color);
    blit_particles(screen, mid_flame, mid_particles, mid_particle_color);
    blit_particles(screen, upper_flame, upper_particles, upper_particle_color);
    
    render_rocket(screen, rocket_x, screen->h - jet_flame_h - rocket_size*8, rocket_size, rocket_color);
    
    SDL_Flip(screen);
  }
  //main loop end
  
  SDL_FreeSurface(screen);
  return 0;
}