#pragma once

#include <istream>
#include <type_traits>
#include <vector>
#include <memory>

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
  static Keyboard & getInstance();

  void signUpKey(std::shared_ptr<Key> key);
  bool listen() const;

  friend std::istream & operator>>(std::istream &, const Keyboard &);

private:
  // Last key pressed on the keyboard
  char keyPressed;
  // List of observators subscribed
  std::vector<std::shared_ptr<Key>> observators;
  void setKeyPressed(char c);
};

std::istream & operator>>(std::istream &, const Keyboard &);
