#ifndef SDL_COLORS_H
#define SDL_COLORS_H_

struct Colour {
  char r, g, b;
};

extern const Colour WHITE{'\xff','\xff','\xff'};
extern const Colour BLACK{'\x0', '\x0', '\x0'};


#endif // SDL_COLORS_H