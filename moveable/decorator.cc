#include "decorator.h"
#include "moveable.h"
#include <memory>
#include <iostream>

using namespace std;

Decorator::Decorator(unique_ptr<Moveable> component) : component{std::move(component)} {}
Decorator::~Decorator(){};

Decorator::Decorator(const Decorator &o) {
    cout << "decorator copy ctor" << endl;
    component = o.component->clone();
}