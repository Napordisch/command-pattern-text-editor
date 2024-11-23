#include "shell.h"

#include <iostream>
#include <sstream>
#include <string>

#include "commands.h"

Shell::Shell(Receiver* _document, CommandHistory* _history)
    : document(_document), history(_history) {}

bool IsInt(const std::string& checked_string) {
  for (char c : checked_string) {
    if (!isdigit(c)) return false;
  }
  return true;
}

void PrintWithEmptyLines(const std::string& printed_string) {
  std::cout << '\n';
  std::cout << printed_string << '\n';
  std::cout << '\n';
}

std::string GetAddedString(std::istringstream& stream) {
  std::string added_string;
  std::string word;
  while (stream >> word) {
    added_string.append(word + " ");
  }
  return added_string.substr(0, added_string.length() - 1);
}

void Shell::RunUI() {
  static const std::string help =
      "i <number> <content> - insert after line\na <content> - append\np "
      "<content> - prepend\nd <number> - delete line \nb - delete last line "
      "\nu - undo\nr - redo\nq - quit";
  PrintWithEmptyLines(help);
  bool running = true;
  while (running) {
    document->Show();
    std::cout << "> ";
    using std::cin;

    std::string command_string;
    std::getline(cin, command_string);
    std::istringstream command_stream(command_string);
    std::string command_name;

    command_stream >> command_name;
    if (command_name == "q") {
      break;
    }
    if (command_name == "u" || command_name == "r") {
      if (command_name == "u") {
        bool undo_result = history->UndoLast();
        if (!undo_result) {
          std::cout << "No changes before" << "\n";
        }
      }
      if (command_name == "r") {
        bool redo_result = history->Redo();
        if (!redo_result) {
          std::cout << "Nothing was undone" << '\n';
        }
      }
      continue;
    }

    Command* current_command;

    if (command_name == "i" || command_name == "d") {
      std::string _line_number;
      command_stream >> _line_number;

      if (!IsInt(_line_number)) {
        PrintWithEmptyLines(
            "This command requires a line number as a second argument!");
        PrintWithEmptyLines(help);
        continue;
      }
      unsigned int line_number = stoi(_line_number);

      if (command_name == "i") {
        InsertLineCommand* _current_command = new InsertLineCommand(document);
        _current_command->SetLine(line_number);
        _current_command->SetInsertedString(GetAddedString(command_stream));
        current_command = _current_command;
      } else if (command_name == "d") {
        DeleteLineCommand* _current_command = new DeleteLineCommand(document);
        _current_command->SetLine(line_number);
        current_command = _current_command;
      }
    }

    else if (command_name == "a" || command_name == "p") {
      std::string added_string = GetAddedString(command_stream);
      if (command_name == "a") {
        AppendLineCommand* _current_command = new AppendLineCommand(document);
        _current_command->SetAppendedString(added_string);
        current_command = _current_command;
      }
      if (command_name == "p") {
        PrependLineCommand* _current_command = new PrependLineCommand(document);
        _current_command->SetPrependedString(added_string);
        current_command = _current_command;
      }
    }

    else if (command_name == "b") {
      current_command = new DeleteLastLineCommand(document);
    } else {
      PrintWithEmptyLines("No such command");
      PrintWithEmptyLines(help);
      continue;
    }
    current_command->Execute();
    history->AddCommand(current_command);
  }
}