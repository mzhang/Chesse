#include "sdl_wrap.h"
#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <memory>

using namespace std;

int SDL_Runner::x = 0;

void Screen::draw_rect(short int xloc, short int yloc, unsigned short int w, unsigned short int h, const Colour c)
{
  // No longer capped at 10 rects, we have a vector now.
  rects.emplace_back(unique_ptr<SDL_Rect>{new SDL_Rect{xloc, yloc, w, h}});
  SDL_FillRect(screen, rects.back().get(), SDL_MapRGB(screen->format, c.r, c.g, c.b));
}

void Screen::update()
{
  int ret = SDL_Flip(screen);
  if (ret == -1)
  {
    cerr << "Error flipping screen!" << endl;
  }
  rects.clear();

  // All rects are erased each update.
}

void Clock::start()
{
  started = true;
  initTick = SDL_GetTicks();
}

int Clock::getTicks()
{
  if (started)
  {
    return SDL_GetTicks() - initTick;
  }
  return 0;
}

void Screen::draw_text(short int xloc, short int yloc, unsigned short int w, unsigned short int h, string text, int font_size, Colour c)
{
  if( TTF_Init() == -1 ) {
    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
  }
  TTF_Font *font = TTF_OpenFont( "/u1/ymulki/cs247/Chesse/graphics/resources/Roboto-Regular.ttf", font_size);
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color{c.r, c.g, c.b, 0});
  if (textSurface == nullptr)
  {
    cerr << "Could not load text surface: " << text << endl;
    return;
  }
  unique_ptr<SDL_Rect> text_rect =  unique_ptr<SDL_Rect>{new SDL_Rect{xloc, yloc, w, h}};
  SDL_BlitSurface(textSurface, nullptr, screen, text_rect.get());
  SDL_FreeSurface(textSurface);
  TTF_CloseFont(font);
}

void Screen::draw_image(short int xloc, short int yloc, unsigned short int w, unsigned short int h, const string &image_path)
{
  SDL_Surface* optimizedSurface = NULL;
  int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) )
  {
      printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
  }
  string full_path = "/u1/ymulki/cs247/Chesse/graphics/resources/" + image_path;
  SDL_Surface* loaded_image_surface = IMG_Load(full_path.c_str());
  if (loaded_image_surface == nullptr)
  {
    cerr << "Could not load asset: " << full_path << endl;
    return;
  }
  optimizedSurface = SDL_ConvertSurface(loaded_image_surface, screen->format, 0 );
  if( optimizedSurface == NULL )
  {
      printf( "Unable to optimize image %s! SDL Error: %s\n", full_path.c_str(), SDL_GetError() );
  }
  unique_ptr<SDL_Rect> image_rect =  unique_ptr<SDL_Rect>{new SDL_Rect{xloc, yloc, w, h}};
  SDL_BlitSurface(loaded_image_surface, nullptr, screen, image_rect.get());
  SDL_FreeSurface(loaded_image_surface);
  SDL_FreeSurface(optimizedSurface);
}