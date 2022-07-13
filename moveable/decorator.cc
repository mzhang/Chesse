#include "decorator.h"
#include "moveable.h"
#include <memory>
#include <iostream>

using namespace std;

Decorator::Decorator(Moveable *component) : component{component} { cout << "decorator ctor" << endl;};
Decorator::~Decorator(){};

Decorator::Decorator(const Decorator &o) {
    cout << "decorator copy ctor" << endl;
    component = o.component->clone();
}