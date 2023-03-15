#include "KeyExclamation.hpp"
#include "KeyDecorator.hpp"

std::string KeyExclamation::activate() const {
  return std::string(KeyDecorator::activate() + "Decorator: !");
}

