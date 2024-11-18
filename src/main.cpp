#include <iostream>
#include <string>

#include "commands.h"
#include "receiver.h"

void PrintDocWithNewlines(const Receiver& _text_doc) {
  std::cout << '\n';
  _text_doc.Show();
  std::cout << '\n';
}

int main() {
  Receiver text_doc("test line\nsecond init line");

  Command* insert_line_command =
      new InsertLineCommand("inserted string", &text_doc, 1);

  insert_line_command->Execute();
  PrintDocWithNewlines(text_doc);

  insert_line_command->Undo();
  PrintDocWithNewlines(text_doc);

  Command* prepend_line_command =
      new PrependLineCommand("prepended string", &text_doc);
  prepend_line_command->Execute();
  PrintDocWithNewlines(text_doc);

  prepend_line_command->Undo();
  PrintDocWithNewlines(text_doc);
  delete insert_line_command;
  delete prepend_line_command;
}
