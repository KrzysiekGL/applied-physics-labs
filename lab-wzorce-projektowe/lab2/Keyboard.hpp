#pragma once

#include <istream>
#include <memory>
#include <map>

#include "Key.hpp"

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
   void signUpKey(std::unique_ptr<Key> && key);
  // Check wheter there are any receivers for the observer
  bool haveReceivers() const;

  friend std::istream & operator>>(std::istream &, Keyboard &);

private:
  // Last key pressed on the keyboard
  char keyPressed;
  // List of observators subscribed
  std::map<char, std::unique_ptr<Key>> observators;
};

std::istream & operator>>(std::istream &, Keyboard &);

