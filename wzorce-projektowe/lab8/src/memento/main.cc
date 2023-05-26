#include <iostream>
#include <memory>

#include "Originator.hpp"
#include "CareTaker.hpp"

int main(int argc, char ** argv) {
  Originator originator(1,2);

  CareTaker careTaker;
  careTaker.saveMemento(originator.createMemento());

  std::cout << originator.getField1() << ' ' <<  originator.getField2() << '\n';
  originator.alterFields();
  std::cout << originator.getField1() << ' ' <<  originator.getField2() << '\n';

  careTaker.restoreMemento();
  std::cout << originator.getField1() << ' ' <<  originator.getField2() << '\n';

  return 0;
}
