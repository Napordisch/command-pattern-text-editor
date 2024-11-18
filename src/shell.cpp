#include "shell.h"
#include "commands.h"
#include <iostream>
#include <string>

Shell::Shell(Receiver *_document) : document(_document) {}

void Shell::RunUI() {
  std::string help = "i <number> <content> - insert after line\na <content> - append\np <content> - prepend\nd <number> - delete line \nb - delete last line \nu - undo\nr - redo";
  std::cout << help;
  std::cout << "\n";
  bool running = true;
  while (true) {
    std::cout << "> ";
    bool valid_command = true;
    std::string command;
    std::cin >> command;
    Command *action;
    action = nullptr;
    if (command == "i") {
      unsigned int line_number;
      std::string inserted_string;
      std::cin >> line_number;
      std::cin >> inserted_string;
      action = new InsertLineCommand(inserted_string, document, line_number);
    } else if (command == "a") {
      std::string appended_string;
      std::cin >> appended_string;
      action = new AppendLineCommand(appended_string, document);
    } else if (command == "p") {
      std::string prepended_string;
      std::cin >> prepended_string;
      action = new PrependLineCommand(prepended_string, document);
    } else if (command == "d") {
      unsigned int line_number;
      action = new DeleteLineCommand(line_number, document);
    }  else if (command == "b") {
      action = new DeleteLastLineCommand(document);
    } else if (command == "u") {
      Command *last_command = undo_list.top();
      undo_list.pop();
      last_command -> Undo();
      redo_list.push(last_command);
    } else if (command == "r") {
      Command *last_undone = redo_list.top();
      redo_list.pop();
      last_undone->Execute();
      undo_list.push(last_undone);
    } else {
      std::cout << help;
      valid_command = false;
    }
    if (action != nullptr) {
      action->Execute();
      undo_list.push(action);
      ClearRedo();
    }
    if (valid_command) {
      std::cout << '\n';
      std::cout << document->GetContent();
      std::cout << '\n';
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max());
  }
}

Shell::~Shell() {
  while (!undo_list.empty()) {
    delete undo_list.top();
    undo_list.pop();
  }
  while (!redo_list.empty()) {
    delete redo_list.top();
    redo_list.pop();
  }
}