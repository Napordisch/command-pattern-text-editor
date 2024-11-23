#include "history.h"

#include "commands.h"

void CommandHistory::ClearRedo() {
  while (!redo_list.empty()) {
    redo_list.pop();
  }
}

CommandHistory::~CommandHistory() {
  while (!undo_list.empty()) {
    delete undo_list.top();
    undo_list.pop();
  }
  while (!redo_list.empty()) {
    delete redo_list.top();
    redo_list.pop();
  }
}

void CommandHistory::AddCommand(Command *the_command) {
  ClearRedo();
  undo_list.push(the_command);
}

bool CommandHistory::UndoLast() {
  if (undo_list.empty()) {
    return false;
  }
  undo_list.top()->Undo();
  redo_list.push(undo_list.top());
  undo_list.pop();
  return true;
}

bool CommandHistory::Redo() {
  if (redo_list.empty()) {
    return false;
  }
  redo_list.top()->Execute();
  undo_list.push(redo_list.top());
  redo_list.pop();
  return true;
}