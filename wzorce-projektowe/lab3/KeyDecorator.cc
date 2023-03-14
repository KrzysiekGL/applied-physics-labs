#include "KeyDecorator.hpp"

std::string KeyDecorator::activate() const {
  return keyInterface->activate();
}
