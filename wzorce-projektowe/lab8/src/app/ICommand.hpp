#pragma once

class ICommand {
public:
  ICommand() {}
  virtual ~ICommand() {}

  virtual void execute() = 0;
};
