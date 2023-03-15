#include "Keyboard.hpp"

Keyboard & Keyboard::getInstance() {
    static Keyboard keyboard; // Meyers Singleton; thread safe
    return keyboard;
}

bool Keyboard::haveReceivers() const {
  return !subscribed.empty();
}

void Keyboard::subscribeKey(std::shared_ptr<KeyInterface> key) {
  subscribed.emplace(key->getKey(), key);
}

std::istream & operator>>(std::istream & is, Keyboard & obj) {
  std::cout << "Keyboard is waiting for input: ";
  is >> obj.keyPressed;

  auto node_handle = obj.subscribed.extract(obj.keyPressed);
  if(node_handle)
    std::cout << node_handle.mapped()->activate() << std::endl;

  return is;
}

