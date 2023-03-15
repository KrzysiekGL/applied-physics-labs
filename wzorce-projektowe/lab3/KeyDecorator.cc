#include "KeyDecorator.hpp"

std::string KeyDecorator::activate() const {
  return keyInterface->activate();
}

char KeyDecorator::getKey() const {
  return keyInterface->getKey();
}
