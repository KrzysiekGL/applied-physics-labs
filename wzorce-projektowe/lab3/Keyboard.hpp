#pragma once

#include <iostream>
#include <istream>
#include <memory>
#include <map>

#include "KeyInterface.hpp"

class Keyboard {
private:
  // Define default constructor and make it private
  Keyboard(){};
  // Delete copy constructor
  Keyboard(const Keyboard&)=delete;
  // Delete assign operator
  Keyboard & operator=(const Keyboard&)=delete;

public:
  // Meyers Singleton (constructor)
  static Keyboard & getInstance();
  // Register a receiver for the observer
   void subscribeKey(std::shared_ptr<KeyInterface> key);
  // Check wheter there are any receivers for the observer
  bool haveReceivers() const;
  // Handle Keyboard input
  friend std::istream & operator>>(std::istream &, Keyboard &);

private:
  // Last key pressed on the keyboard
  char keyPressed;
  // List of observators subscribed
  std::map<char, std::shared_ptr<KeyInterface>> subscribed;
};

std::istream & operator>>(std::istream &, Keyboard &);

