#pragma once

#include "KeyInterface.hpp"
#include <string>
#include <memory>

class KeyDecorator : public KeyInterface {
protected:
  std::unique_ptr<KeyInterface> keyInterface;
public:
  KeyDecorator(std::unique_ptr<KeyInterface> && keyInterface)
    : keyInterface(std::move(keyInterface)){}
  std::string activate() const override;
};
