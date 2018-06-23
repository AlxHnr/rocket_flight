#include <particle.h>

void init_particles(particle *particle_array, int elements, int x, int y, int w, int h)
{
  int particle_counter = 0;
  while(particle_counter < elements)
  {
    particle_array[particle_counter].x = x + rand() % (w + 1);
    particle_array[particle_counter].y = y + rand() % (h + 1);
    particle_array[particle_counter].dest_x = x;
    particle_array[particle_counter].dest_y = y + h;
    particle_counter++;
  }
}
void init_sphere(particle *particle_array, int elements, int x, int y, int r)
{
  int particle_counter = 0;
  
  init_particles(particle_array, elements, x - r, y - r, r * 2, r * 2);
  
  while(particle_counter < 5)
  {
    render_sphere(particle_array, elements, x, y, r, 5);
    particle_counter++;
  }
}

void move_particles(particle *particle_array, int elements, int x, int y)
{
  int particle_counter = 0;
  while(particle_counter < elements)
  {
    particle_array[particle_counter].x += x;
    particle_array[particle_counter].y += y;
    particle_counter++;
  }
}

void render_jet_flame(particle *particle_array, int elements, int x, int y, int w, int h, int speed)
{
  int particle_counter = 0;
  int max_movement;
  
  if(h > w)
    max_movement = (int)(h/w) + 1;
  else if(w > h)
    max_movement = (int)(w/h) + 1;
  else
    max_movement = 2;
  
  while(particle_counter < elements)
  {
    if(particle_array[particle_counter].y < particle_array[particle_counter].dest_y - rand() % h/(int)(rand() % w + 1))
    {
      if(particle_array[particle_counter].x < particle_array[particle_counter].dest_x + rand() % (int)(w/2))
        particle_array[particle_counter].x += rand() % max_movement;
      if(particle_array[particle_counter].x > particle_array[particle_counter].dest_x - rand() % (int)(w/2))
        particle_array[particle_counter].x -= rand() % max_movement;
      
      if(speed > 1)
        particle_array[particle_counter].y += rand() % speed + 1;
      else
        particle_array[particle_counter].y++;
    }
    else
    {
      particle_array[particle_counter].y = y;
      particle_array[particle_counter].x = x + rand() % w;
      particle_array[particle_counter].dest_x = x + (int)(w/2);
      particle_array[particle_counter].dest_y = y + h;
    }
    
    if(rand() % (elements) == 0)
    {
      break;
    }
    particle_counter++;
  }
}
void render_falling_particles(particle *particle_array, int elements, int x, int y, int w, int h, int speed)
{
  int particle_counter = 0;
  
  while(particle_counter < elements)
  {
    if(particle_array[particle_counter].y < particle_array[particle_counter].dest_y)
    {
      if(speed > 1)
        particle_array[particle_counter].y += rand() % speed + 1;
      else
        particle_array[particle_counter].y += 1;
    }
    else
    {
      particle_array[particle_counter].y = y;
      particle_array[particle_counter].x = x + rand() % w;
      particle_array[particle_counter].dest_y = y + h;
      particle_array[particle_counter].dest_x = x;
    }
    particle_counter++;
  }
}
void render_sphere(particle *particle_array, int elements, int x, int y, int r, int speed)
{
  int particle_counter = 0;
  
  speed += 5;
  
  while(particle_counter < elements)
  {
    /* left side */
    if(particle_array[particle_counter].x + rand() % speed < x)
    {
      if(particle_array[particle_counter].y + rand() % speed < y)
      {
        /* upper left side */
        if(particle_array[particle_counter].y < y - (Sint16)(sqrt(pow(r, 2) - pow(x - particle_array[particle_counter].x, 2))))
        {
          particle_array[particle_counter].dest_y = rand() % speed + 1;
        }
        if(particle_array[particle_counter].x < x - (Sint16)(sqrt(pow(r, 2) - pow(y - particle_array[particle_counter].y, 2))))
        {
          particle_array[particle_counter].dest_x = rand() % speed + 1;
        }
      }
      else
      {
        /* lower left side */
        if(particle_array[particle_counter].y > y + (Sint16)(sqrt(pow(r, 2) - pow(x - particle_array[particle_counter].x, 2))))
        {
          particle_array[particle_counter].dest_y = -1 * rand() % speed + 1;
        }
        if(particle_array[particle_counter].x < x - (Sint16)(sqrt(pow(r, 2) - pow(particle_array[particle_counter].y - y, 2))))
        {
          particle_array[particle_counter].dest_x = rand() % speed + 1;
        }
      }
    }
    /* right side */
    else
    {
      if(particle_array[particle_counter].y + rand() % speed < y)
      {
        /* upper right side */
        if(particle_array[particle_counter].y < y - (Sint16)(sqrt(pow(r, 2) - pow(particle_array[particle_counter].x - x, 2))))
        {
          particle_array[particle_counter].dest_y = rand() % speed + 1;
        }
        if(particle_array[particle_counter].x > x + (Sint16)(sqrt(pow(r, 2) - pow(y - particle_array[particle_counter].y, 2))))
        {
          particle_array[particle_counter].dest_x = -1 * rand() % speed + 1;
        }
      }
      else
      {
        /* lower right side */
        if(particle_array[particle_counter].y > y + (Sint16)(sqrt(pow(r, 2) - pow(particle_array[particle_counter].x - x, 2))))
        {
          particle_array[particle_counter].dest_y = -1 * rand() % speed + 1;
        }
        if(particle_array[particle_counter].x > x + (Sint16)(sqrt(pow(r, 2) - pow(particle_array[particle_counter].y - y, 2))))
        {
          particle_array[particle_counter].dest_x = -1 * rand() % speed + 1;
        }
      }
    }
    
    /* uses dest_? as movement value */
    if(particle_array[particle_counter].dest_x > speed)
    {
      if(rand() % 2)
        particle_array[particle_counter].dest_x = speed;
      else
        particle_array[particle_counter].dest_x = -1 * speed;
    }
    if(particle_array[particle_counter].dest_y > speed)
    {
      if(rand() % 2)
        particle_array[particle_counter].dest_y = speed;
      else
        particle_array[particle_counter].dest_y = -1 * speed;
    }
    
    particle_array[particle_counter].x += particle_array[particle_counter].dest_x;
    particle_array[particle_counter].y += particle_array[particle_counter].dest_y;
    
    particle_counter++;
  }
}

void blit_particles(SDL_Surface *screen, particle *particle_array, int elements, unsigned char r, unsigned char g, unsigned char b)
{
  int particle_counter = 0;
  
  while(particle_counter < elements)
  {
    boxRGBA(screen, particle_array[particle_counter].x, particle_array[particle_counter].y, particle_array[particle_counter].x + 1, particle_array[particle_counter].y + 1, r, g, b, 25);
    particle_counter++;
  }
}