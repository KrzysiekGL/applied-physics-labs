#pragma once

#include <memory>
#include <vector>

#include "BoxWindow.hpp"

// Meyers Singleton
class Application {
private:
  Application() {};
  Application(const Application &) = delete;
  Application & operator=(const Application &) = delete;
public:
  static Application & getInstance();

  void addBoxWindow(const char *);
  void showWindows();

  // Commands for the BoxWindow
  class AddTextCommand : public ICommand {
  public:
    AddTextCommand(std::shared_ptr<BoxWindow> boxWindow) : boxWindow(boxWindow) {}
    void execute() override;
  private:
    std::shared_ptr<BoxWindow> boxWindow;
  };

  class RemoveTextCommand : public ICommand {
  public:
    RemoveTextCommand(std::shared_ptr<BoxWindow> boxWindow) : boxWindow(boxWindow) {}
    void execute() override;
  private:
    std::shared_ptr<BoxWindow> boxWindow;
  };

  class SaveCommand : public ICommand {
  public:
    SaveCommand(std::shared_ptr<BoxWindow> boxWindow) : boxWindow(boxWindow) {}
    void execute() override;
  private:
    std::shared_ptr<BoxWindow> boxWindow;
  };

  class UndoCommand : public ICommand {
  public:
    UndoCommand(std::shared_ptr<BoxWindow> boxWindow) : boxWindow(boxWindow) {}
    void execute() override;
  private:
    std::shared_ptr<BoxWindow> boxWindow;
  };

private:
  std::vector<std::shared_ptr<BoxWindow>> boxWindows;
};
