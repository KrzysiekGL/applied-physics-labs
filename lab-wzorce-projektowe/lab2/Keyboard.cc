#include "Keyboard.hpp"

Keyboard & getInstance() {
	static Keyboard keyboard;
	return keyboard;
}
