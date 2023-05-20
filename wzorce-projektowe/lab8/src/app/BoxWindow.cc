#include "BoxWindow.hpp"

static void dummyCommand() {}

bool BoxWindow::show() {
  IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context");

  // Main body of the window
  bool collapsed;
  if(!(collapsed = ImGui::Begin(title.c_str()))) {
    // Early out if the window is collapsed (false), as an optimization
    ImGui::End();
    return collapsed;
  }

  ImGui::Text("This is a button for usage with the command:");
  if(ImGui::Button("Execute Command"))
    dummyCommand();

  // Main window end
  ImGui::End();
  return collapsed;
}
