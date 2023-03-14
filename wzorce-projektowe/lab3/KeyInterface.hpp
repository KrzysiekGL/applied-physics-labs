#pragma once

class KeyInterface {
public:
	virtual ~KeyInterface() {}
	virtual void activate() const = delete;
private:
	char key;
}
