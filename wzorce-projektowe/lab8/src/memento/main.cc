#include <iostream>
#include <memory>

#include "Originator.hpp"

int main(int argc, char ** argv) {
  Originator originator(1,2);
  std::unique_ptr<Originator::Memento> memento = originator.createMemento();

  std::cout << originator.getField1() << ' ' <<  originator.getField2() << '\n';
  originator.alterFields();
  std::cout << originator.getField1() << ' ' <<  originator.getField2() << '\n';

  memento->restore();
  std::cout << originator.getField1() << ' ' <<  originator.getField2() << '\n';

  return 0;
}
