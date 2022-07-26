#ifndef SDL_WRAP_H_
#define SDL_WRAP_H_

#include <SDL/SDL.h>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "colours.h"

// Class that represents your screen, currently can be used to draw rectangles.
class Screen {
  SDL_Surface *screen;
  std::string screenName;
  std::vector<std::unique_ptr<SDL_Rect>> rects;

public:
  Screen(int w = 652, int h = 652, std::string screenName = "Chesse");
  Screen(const Screen &) = delete;
  Screen(Screen &&o);
  Screen &operator=(const Screen &) = delete;
  Screen &operator=(Screen &&o) = delete;
  ~Screen();

  void draw_rect(short int x, short int y, unsigned short int w,
                 unsigned short int h, const Colour c);
  void draw_text(short int x, short int y, unsigned short int w,
                 unsigned short int h, std::string text, int font_size,
                 Colour c);
  void draw_image(short int x, short int y, unsigned short int w,
                  unsigned short int h, const std::string &image_path);

  void update();
  int getWidth();
  int getHeight();
};

#endif // SDL_WRAP_H_
