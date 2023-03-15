#pragma once

#include "KeyDecorator.hpp"
#include "KeyInterface.hpp"
#include <memory>
#include <string>

class KeyExclamation : public KeyDecorator {
public:
  KeyExclamation(std::shared_ptr<KeyInterface> k) : KeyDecorator(k) {}
  std::string activate() const override;
};

