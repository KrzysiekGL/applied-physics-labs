#include "Key.hpp"

char Key::getKey() const {
  return key;
}

void Key::activate() {
  std::cout << "Key " << getKey() << " activated. Goodbye\n";
}

