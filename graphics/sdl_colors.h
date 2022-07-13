#ifndef SDL_COLORS_H
#define SDL_COLORS_H_

struct Colour {
  char r, g, b;
};

const Colour WHITE{'\xff','\xff','\xff'};
const Colour BLACK{'\x0', '\x0', '\x0'};
const Colour BROWN{'\x99','\x99','\x99'};


#endif // SDL_COLORS_H