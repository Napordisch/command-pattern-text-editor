#ifndef SHELL_H
#define SHELL_H
#include <iostream>
#include <stack>
#include <string>

#include "commands.h"
#include "history.h"
#include "receiver.h"

class Shell {  // invoker
 private:
  Receiver *document;
  CommandHistory *history;

 public:
  Shell(Receiver *_document, CommandHistory *_history);
  void RunUI();
};
#endif