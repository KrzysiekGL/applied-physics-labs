#pragma once

#include <forward_list>
#include <memory>

#include "IMemento.hpp"

class CareTaker {
public:
  void saveMemento(std::unique_ptr<IMemento> memento);
  void restoreMemento();

private:
  std::forward_list<std::unique_ptr<IMemento>> mementos;
};
