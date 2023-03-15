#pragma once

#include "KeyInterface.hpp"
#include <string>
#include <memory>

class KeyDecorator : public KeyInterface {
protected:
  std::shared_ptr<KeyInterface> keyInterface;
public:
  KeyDecorator(std::shared_ptr<KeyInterface> keyInterface) : keyInterface(keyInterface) {}
  std::string activate() const override;
  char getKey() const override;
};

