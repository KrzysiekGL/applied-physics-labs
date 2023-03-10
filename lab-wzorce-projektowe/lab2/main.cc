#include <iostream>
#include <memory>
#include <pthread.h>
#include <vector>

#include "Keyboard.hpp"
#include "Key.hpp"

int main(int argc, char ** argv, char ** env) {
  Keyboard & keyboard = Keyboard::getInstance();

  std::vector<std::shared_ptr<Key>> keys;
  for(int i=0; i<5; ++i) /* initialize keys: a, b, c, d, e */ {
    keys.push_back(std::make_shared<Key>(Key((char)(97+i))));
    keyboard.signUpKey(keys.back());
  }

  while (std::cin >> keyboard) {
  }

  return 0;
}
