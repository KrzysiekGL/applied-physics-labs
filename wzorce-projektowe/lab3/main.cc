#include <iostream>
#include <memory>

#include "Keyboard.hpp"
#include "KeyInterface.hpp"

int main(int argc, char ** argv, char ** env) {
  Keyboard & keyboard = Keyboard::getInstance();

  for(int i=0; i<5; ++i) /* initialize keys: a, b, c, d, e */
    keyboard.signUpKey(std::make_unique<KeyExclamation>((char)('a'+i)));

  while (keyboard.haveReceivers())
    std::cin >> keyboard;

  return 0;
}
