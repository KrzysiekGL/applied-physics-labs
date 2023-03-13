#include "Keyboard.hpp"
#include <ios>
#include <istream>
#include <limits>
#include <memory>

Keyboard & Keyboard::getInstance() {
    static Keyboard keyboard; // Meyers Singleton; thread safe
    return keyboard;
}

bool Keyboard::haveReceivers() const {
  return !observators.empty();
}

void Keyboard::signUpKey(std::unique_ptr<Key> && key) {
  observators.emplace(key->getKey(), std::forward<std::unique_ptr<Key>>(key));
}

std::istream & operator>>(std::istream & is, Keyboard & obj) {
  std::cout << "Keyboard is waiting for input: ";
  is >> obj.keyPressed;

  auto node_handle = obj.observators.extract(obj.keyPressed);
  if(node_handle) node_handle.mapped()->activate();

  return is;
}

