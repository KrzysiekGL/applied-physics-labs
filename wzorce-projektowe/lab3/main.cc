#include <iostream>
#include <memory>

#include "Keyboard.hpp"
#include "KeyInterface.hpp"
#include "Key.hpp"
#include "KeyExclamation.hpp"
#include "KeyQuestion.hpp"

int main(int argc, char ** argv, char ** env) {
  Keyboard & keyboard = Keyboard::getInstance();

  for(int i=0; i<5; ++i) /* initialize keys: a, b, c, d, e */ {
    std::shared_ptr<KeyInterface> key = std::make_shared<Key>((char)('a'+i));
    if(i==2) key = std::make_shared<KeyExclamation>(key);
    if(i==4) key = std::make_shared<KeyQuestion>(key);
    keyboard.subscribeKey(key);
  }

  while (keyboard.haveReceivers())
    std::cin >> keyboard;

  return 0;
}
