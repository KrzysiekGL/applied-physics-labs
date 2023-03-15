#pragma once

#include "KeyInterface.hpp"
#include "KeyDecorator.hpp"
#include <memory>
#include <string>

class KeyQuestion : public KeyDecorator {
public:
  KeyQuestion(std::shared_ptr<KeyInterface> k) : KeyDecorator(k) {}
  std::string activate() const override;
};

