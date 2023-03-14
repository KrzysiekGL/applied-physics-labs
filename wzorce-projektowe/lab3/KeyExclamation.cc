#include "KeyExclamation.hpp"

std::string KeyExclamation::activate() const {
  return std::string(KeyDecorator::activate() + "!");
}
