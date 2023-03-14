#pragma once

#include "KeyDecorator.hpp"
#include "KeyInterface.hpp"
#include <memory>
#include <string>

class KeyExclamation : public KeyDecorator {
public:
  KeyExclamation(std::unique_ptr<KeyInterface> && keyInterface)
    : KeyDecorator(std::move(keyInterface)) {}
  std::string activate() const override;
};
