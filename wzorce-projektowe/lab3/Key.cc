#include "Key.hpp"

std::string Key::activate() const {
  return std::string("Key " + std::string(1, getKey()) + " activated. Goodbye");
}

