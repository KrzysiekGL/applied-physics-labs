#pragma once

#include <iostream>

class Key {
public:
  Key(char key) : key(key) {}
  char getKey() const;
  void activate();
private:
  char key;
};
