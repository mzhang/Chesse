#ifndef SDL_WRAP_H_
#define SDL_WRAP_H_

#include <SDL/SDL.h>
#include <string>
#include <vector>
#include <utility>
#include <memory>

#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "sdl_colors.h"

// This class just handles the start and end of SDL, just need to declare one at the start of your program,
// either globally or at the begining of main, and then do nothing with it.
class SDL_Runner {
  static int x;
 public:
  SDL_Runner() {
    if (!x) {
      SDL_Init(SDL_INIT_EVERYTHING);
      ++x;
    }
  }
  ~SDL_Runner() {
      TTF_Quit();
      IMG_Quit();
      SDL_VideoQuit(); 
      SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
      SDL_Quit();
    }
};


// Class that represents your screen, currently can be used to draw rectangles.
class Screen {
  SDL_Surface *screen;
  std::string screenName;
  std::vector<std::unique_ptr<SDL_Rect>> rects;
 public:
  Screen(int w=652, int h=652, std::string screenName="Chesse") : screen{SDL_SetVideoMode(w, h, 32, SDL_SWSURFACE)},
        screenName{screenName},  rects{} {
    SDL_WM_SetCaption(screenName.c_str(), nullptr);
  }
  Screen(const Screen &) = delete;
  Screen(Screen && o) : screen{o.screen}, screenName{std::move(o.screenName)}, rects{std::move(o.rects)} { o.screen = nullptr; }
  Screen &operator=(const Screen &) = delete;
  Screen &operator=(Screen &&o) = delete;
  ~Screen() {
    if (screen) {
      SDL_FreeSurface(screen);
    }
  }

  void draw_rect(short int x, short int y, unsigned short int w, unsigned short int h, const Colour c);
  void draw_text(short int x, short int y, unsigned short int w, unsigned short int h,
    std::string text, int font_size, Colour c);
  void draw_image(short int x, short int y, unsigned short int w, unsigned short int h,
    const std::string &image_path);

  void update();
  int getWidth() { return screen->w; }
  int getHeight() { return screen->h; }
};


// For timing framerate - we can't have our
// loop for a GUI with input running at the
// max speed it can, it's too fast.
class Clock {
  int initTick = 0;
  bool started = false;
 public:
  Clock() {}
  void start();
  int getTicks();
};

#endif // SDL_WRAP_H_