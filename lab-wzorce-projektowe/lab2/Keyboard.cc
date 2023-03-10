#include "Keyboard.hpp"

Keyboard & Keyboard::getInstance() {
    static Keyboard keyboard; // Meyers Singleton; thread safe
    return keyboard;
}

bool Keyboard::listen() const {
  return bool(observators.size());
}

void Keyboard::signUpKey(std::shared_ptr<Key> key) {
  observators.push_back(key);
}

void Keyboard::setKeyPressed(char c) {
  keyPressed = c;
}

std::istream & operator>>(std::istream & is, const Keyboard & obj) {
  std::cout << "Keyboard is waiting for input...";
  char c;
  std::cin >> c;
  std::cout << "Keybaord read letter " << c << '\n';
  obj.setKeyPressed(c);
  return is;
}

