#include "sdl_wrap.h"
#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <memory>

using namespace std;

int SDL_Runner::x = 0;

void Screen::draw_rect(short int xloc, short int yloc, unsigned short int w, unsigned short int h, const Colour c)
{
  // No longer capped at 10 rects, we have a vector now.
  rects.emplace_back(new SDL_Rect{xloc, yloc, w, h});
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
  unique_ptr<SDL_Surface> text_surface = unique_ptr<SDL_Surface>{TTF_RenderText_Solid(TTF_OpenFont("resources/Roboto-Regular.ttf", font_size), text.c_str(), SDL_Color{c.r, c.g, c.b, 0})};
  SDL_Rect text_rect{xloc, yloc, w, h};
  SDL_BlitSurface(text_surface.get(), nullptr, screen, &text_rect);
  SDL_FreeSurface(text_surface.get());
}

void Screen::draw_image(short int xloc, short int yloc, unsigned short int w, unsigned short int h, const string &image_path)
{
  // Image path is relative to resources directory
  string full_path = "resources/" + image_path;
  shared_ptr<SDL_Surface> loaded_image_surface{SDL_LoadBMP(full_path.c_str())};
  if (loaded_image_surface == nullptr)
  {
    cerr << "Could not load asset: " << image_path << endl;
    return;
  }
  shared_ptr<SDL_Rect> image_rect(new SDL_Rect{xloc, yloc, w, h});
  SDL_BlitSurface(loaded_image_surface.get(), nullptr, screen, image_rect.get());
  SDL_FreeSurface(loaded_image_surface.get());
}