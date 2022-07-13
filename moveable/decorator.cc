#include "decorator.h"
#include "moveable.h"
#include <memory>

using namespace std;

Decorator::Decorator(Moveable *component) : component{component} {};
Decorator::~Decorator(){};
