#include "Originator.hpp"
#include <memory>

std::unique_ptr<Originator::Memento> Originator::createMemento() {
  return std::move(std::make_unique<Memento>(Memento(std::move(*this))));
}

void Originator::alterFields() {
  field1 *= 2;
  field2 *= 2;
}

Originator::Memento::Memento(Originator && originator) {
  this->originator = &originator;
  field1 = originator.field1;
  field2 = originator.field2;
}

void Originator::Memento::restore() {
  originator->field1 = field1;
  originator->field2 = field2;
}
