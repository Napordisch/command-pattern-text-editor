#include <iostream>
#include <string>

#include "receiver.h"
#include "shell.h"

void PrintDocWithNewlines(const Receiver &_text_doc) {
  std::cout << '\n';
  _text_doc.Show();
  std::cout << '\n';
}

int main() {
  Receiver document("test start");
  Shell UI(&document);
  UI.RunUI();
}
