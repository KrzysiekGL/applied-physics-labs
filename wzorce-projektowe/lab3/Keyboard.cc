#include "Keyboard.hpp"

Keyboard & Keyboard::getInstance() {
    static Keyboard keyboard; // Meyers Singleton; thread safe
    return keyboard;
}

bool Keyboard::haveReceivers() const {
  return !observators.empty();
}

void Keyboard::signUpKey(std::unique_ptr<KeyInterface> && key) {
  observators.emplace(key->getKey(), std::move(key));
}

std::istream & operator>>(std::istream & is, Keyboard & obj) {
  std::cout << "Keyboard is waiting for input: ";
  is >> obj.keyPressed;

  auto node_handle = obj.observators.extract(obj.keyPressed);
  if(node_handle)
    std::cout << node_handle.mapped()->activate() << std::endl;

  return is;
}

