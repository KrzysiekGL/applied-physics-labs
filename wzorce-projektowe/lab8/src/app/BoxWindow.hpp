#pragma once

#include <string>

#include <imgui.h>

class BoxWindow {
public:
  BoxWindow() : title("BoxWindow") {}
  BoxWindow(const BoxWindow &) = delete;
  BoxWindow(const char * title) : title(title) {}

  bool show();

private:
  const std::string title;
};
