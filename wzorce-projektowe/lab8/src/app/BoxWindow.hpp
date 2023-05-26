#pragma once

#include <string>
#include <memory>

#include <imgui.h>

#include <IMemento.hpp>
#include <CareTaker.hpp>

#include "ICommand.hpp"

class BoxWindow {
public:
  // Memento snapshot container implementation for BoxWindow class
  class Memento : public IMemento {
  public:
    Memento(BoxWindow *);
    void restore() override;
  private:
    BoxWindow * boxWindow;
    uint numberOfTextFields = 0;
  };

  // Manage memento snapshots
  CareTaker careTaker;
  std::unique_ptr<IMemento> createMemento();

  BoxWindow() : title("BoxWindow") {}
  BoxWindow(const char * title) : title(title) {}

  BoxWindow(const BoxWindow &) = delete;
  BoxWindow & operator=(const BoxWindow &) = delete;

  // returns false when window is collapsed
  bool show();

  void setAddText(std::unique_ptr<ICommand>);
  void setRemoveText(std::unique_ptr<ICommand>);
  void setSave(std::unique_ptr<ICommand>);
  void setUndo(std::unique_ptr<ICommand>);

  void addTextField();
  void removeTextField();

private:
  const std::string title;
  std::unique_ptr<ICommand> addText;
  std::unique_ptr<ICommand> removeText;
  std::unique_ptr<ICommand> save;
  std::unique_ptr<ICommand> undo;
  uint numberOfTextFields = 0;
};
