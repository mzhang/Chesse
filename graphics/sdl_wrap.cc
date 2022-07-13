#include "sdl_wrap.h"
#include <string>
#include <iostream>
using namespace std;

int SDL_Runner::x = 0;

void Screen::draw_rect(short int xloc, short int yloc, short int w, short int h, Colour c) {
  // No longer capped at 10 rects, we have a vector now.
  rects.emplace_back(new SDL_Rect{xloc, yloc, w, h});
  SDL_FillRect(screen, rects.back(), SDL_MapRGB(screen->format, c.r, c.g, c.b));
}

void Screen::update() {
  int ret = SDL_Flip(screen);
  if (ret == -1) {
    cerr << "Error flipping screen!" << endl;
  }
  for (auto &p: rects) {
    delete p;
  }
  rects.clear();

  // All rects are erased each update.
}


void Clock::start() {
  started = true;
  initTick = SDL_GetTicks();
}

int Clock::getTicks() {
  if (started) {
    return SDL_GetTicks() - initTick;
  }
  return 0;
}


