#include "Application.hpp"

Application & Application::getInstance() {
  static Application application;
  return application;
}

void Application::addBoxWindow(const char * title = NULL) {
  // Add a new BoxWindow
  if(title)
    boxWindows.push_back(std::move(std::make_shared<BoxWindow>(title)));
  else
    boxWindows.push_back(std::move(std::make_shared<BoxWindow>()));

  // Set it's commands
  std::shared_ptr<BoxWindow> boxWindow = boxWindows.back();
  boxWindow->setAddText(std::move(std::make_unique<AddTextCommand>(boxWindow)));
  boxWindow->setRemoveText(std::move(std::make_unique<RemoveTextCommand>(boxWindow)));
  boxWindow->setSave(std::move(std::make_unique<SaveCommand>(boxWindow)));
  boxWindow->setUndo(std::move(std::make_unique<UndoCommand>(boxWindow)));
}

void Application::showWindows() {
  for(auto boxWindowPtr : boxWindows)
    boxWindowPtr->show();
}

void Application::AddTextCommand::execute() {
  if(boxWindow)
    boxWindow->addTextField();
}

void Application::RemoveTextCommand::execute() {
  if(boxWindow)
    boxWindow->removeTextField();
}

void Application::SaveCommand::execute() {
  if(boxWindow)
    boxWindow->careTaker.saveMemento(boxWindow->createMemento());
}

void Application::UndoCommand::execute() {
  if(boxWindow)
    boxWindow->careTaker.restoreMemento();
}
