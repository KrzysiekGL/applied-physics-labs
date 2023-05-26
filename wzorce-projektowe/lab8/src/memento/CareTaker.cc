#include "CareTaker.hpp"

void CareTaker::saveMemento(std::unique_ptr<IMemento> memento) {
  mementos.push_front(std::move(memento));
}

void CareTaker::restoreMemento() {
  if(!mementos.empty()) {
    std::unique_ptr<IMemento> memento = std::move(mementos.front());
    mementos.pop_front();
    if(memento)
      memento->restore();
  }
}
