#include <iostream>
#include <string>

#include "commands.h"
#include "receiver.h"

int main() {
  Receiver text_doc("test line\nsecond init line");
  Command* insert_line_command = new InsertLineCommand("inserted string", &text_doc, 1);
  insert_line_command->Execute();
  text_doc.Show();
  insert_line_command->Undo();
  text_doc.Show();
  delete insert_line_command;
}
