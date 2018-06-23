#include <render_gfx.h>

void render_rocket(SDL_Surface *screen, int x, int y, int size, unsigned char r, unsigned char g, unsigned char b)
{
  filledTrigonRGBA(screen, x + size*2, y, x + size, y + size, x + size*3, y + size, r, g, b, 255);
  boxRGBA(screen, x + size, y + size, x + size*3, y + size*8, r, g, b, 255);
  filledTrigonRGBA(screen, x + size, y + size*6, x, y + size*8, x + size, y + size*8, r, g, b, 255);
  filledTrigonRGBA(screen, x + size*3, y + size*6, x + size*3, y + size*8, x + size*4, y + size*8, r, g, b, 255);
}