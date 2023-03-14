#pragma once

#include <string>

#include "KeyInterface.hpp"

class Key : public KeyInterface {
public:
  Key(char key) : key(key) {}
  char getKey() const override;
  std::string activate() const override;
private:
  char key;
};
