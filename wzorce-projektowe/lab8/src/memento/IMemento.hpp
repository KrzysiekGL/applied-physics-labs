#pragma once

#include <iostream>

class IMemento {
public:
  IMemento() {}
  IMemento(const IMemento &) = delete;
  virtual void restore() = 0;
};
