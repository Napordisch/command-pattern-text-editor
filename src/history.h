#ifndef HISTORY_H
#define HISTORY_H

#include <stack>

#include "commands.h"

class CommandHistory {
 private:
  std::stack<Command *> undo_list;
  std::stack<Command *> redo_list;
  void ClearRedo();

 public:
  void AddCommand(Command *the_command);
  bool UndoLast();
  bool Redo();
  ~CommandHistory();
};

#endif