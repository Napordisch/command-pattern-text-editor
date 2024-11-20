#include "shell.h"
#include "commands.h"
#include <iostream>
#include <string>
#include <sstream>

Shell::Shell(Receiver *_document) : document(_document) {}

void Shell::RunUI() {
  static const std::string help = "i <number> <content> - insert after line\na <content> - append\np <content> - prepend\nd <number> - delete line \nb - delete last line \nu - undo\nr - redo\nq - quit";
  std::cout << help;
  std::cout << "\n";
  bool running = true;
  while (running) {
    using std::cin;
    std::string command_string;
    std::getline(cin, command_string);
    std::istringstream command_stream(command_string);
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