#pragma once

#include <vector>
#include <memory>

#include "Key.hpp"

class Keyboard {
private:
	// Define default constructor (as private)
	Keyboard(){};
	// Delete copy constructor
	Keyboard(const Keyboard&)=delete;
	// Delete assign operator
	Keyboard & operator=(const Keyboard&)=delete;

public:
	static Keyboard & getInstance();
	void signUp(std::unique_ptr<Key> key);

private:
	// Last key pressed on the keyboard
	char keyPressed;
	// List of observators subscribed
	std::vector<std::unique_ptr<Key>> observators;
	// Event when key pressed
	void onKeyPressed();
};
