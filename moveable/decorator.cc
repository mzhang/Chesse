#include "decorator.h"
#include "moveable.h"
#include <memory>

using namespace std;

Decorator::Decorator(unique_ptr<Moveable> component){};
Decorator::~Decorator(){};
