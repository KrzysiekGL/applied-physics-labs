#pragma once

#include "KeyInterface.hpp"
#include <string>

class Key : public KeyInterface {
public:
  Key(char key) {this->key = key;}
  std::string activate() const override;
  char getKey() const override;
private:
  char key;
};
