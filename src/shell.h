#ifndef SHELL_H
#define SHELL_H
#include "commands.h"
#include "receiver.h"
#include <iostream>
#include <stack>
#include <string>

class Shell { // invoker
private:
  Receiver *document;
  std::stack<Command*> undo_list;
  std::stack<Command*> redo_list;
  void ClearRedo() {
    while (!redo_list.empty()) {
      redo_list.pop();
    }
  }

public:
  Shell(Receiver *_document);
  void RunUI();
  ~Shell();
};
#endif