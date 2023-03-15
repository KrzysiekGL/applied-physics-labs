#include "KeyQuestion.hpp"

std::string KeyQuestion::activate() const {
  return std::string(KeyDecorator::activate() + "Decorator: ?");
}

