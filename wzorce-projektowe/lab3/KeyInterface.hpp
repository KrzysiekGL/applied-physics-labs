#pragma once

#include <string>

class KeyInterface {
public:
  virtual ~KeyInterface() {}
  virtual std::string activate() const = 0;
  virtual char getKey() const = 0;
};
