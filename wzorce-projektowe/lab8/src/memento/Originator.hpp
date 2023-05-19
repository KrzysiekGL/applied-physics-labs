#pragma once

#include <memory>

#include "IMemento.hpp"

class Originator {
public:
  class Memento : public IMemento {
  public:
    Memento(Originator * originator);
    void restore() override;
  private:
    Originator * originator;
    int field1;
    int field2;
  };

  Originator() {}
  Originator(int field1, int field2) : field1(field1), field2(field2) {}

  void alterFields();

  int getField1() { return field1; }
  int getField2() { return field2; }

  std::unique_ptr<Memento> createMemento();

private:
  int field1;
  int field2;
};
