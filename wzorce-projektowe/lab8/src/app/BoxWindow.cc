#include "BoxWindow.hpp"
#include "ICommand.hpp"

BoxWindow::Memento::Memento(BoxWindow * boxWindow) : boxWindow(boxWindow) {
  numberOfTextFields = boxWindow->numberOfTextFields;
}

void BoxWindow::Memento::restore() {
  boxWindow->numberOfTextFields = numberOfTextFields;
}

std::unique_ptr<IMemento> BoxWindow::createMemento() {
  return std::move(std::make_unique<Memento>(this));
}

bool BoxWindow::show() {
  IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context");

  // Main body of the window
  bool collapsed;
  if(!(collapsed = ImGui::Begin(title.c_str()))) {
    // Early out if the window is collapsed (false), as an optimization
    ImGui::End();
    return collapsed;
  }

  for(int i=0; i<numberOfTextFields; ++i) {
    const std::string text = "This is a text field number " + std::to_string(i+1);
    ImGui::Text("%s", text.c_str());
  }

  if(ImGui::Button("Add Text") && addText)
    addText->execute();

  ImGui::SameLine();
  if(ImGui::Button("Remove Text") && removeText)
    removeText->execute();

  ImGui::SameLine();
  if(ImGui::Button("Save State") && save)
    save->execute();

  ImGui::SameLine();
  if(ImGui::Button("Undo Operation") && undo)
    undo->execute();

  // Main window end
  ImGui::End();
  return collapsed;
}

void BoxWindow::setAddText(std::unique_ptr<ICommand> addText) {
  this->addText = std::move(addText);
}

void BoxWindow::setRemoveText(std::unique_ptr<ICommand> removeText) {
  this->removeText = std::move(removeText);
}

void BoxWindow::setSave(std::unique_ptr<ICommand> save) {
  this->save = std::move(save);
}

void BoxWindow::setUndo(std::unique_ptr<ICommand> undo) {
  this->undo = std::move(undo);
}

void BoxWindow::addTextField() {
  numberOfTextFields++;
}

void BoxWindow::removeTextField() {
  if(numberOfTextFields)
    numberOfTextFields--;
}
