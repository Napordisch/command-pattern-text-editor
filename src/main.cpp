#include "commands.h"
#include "receiver.h"
#include <iostream>
#include <string>

int main() {
    Receiver text_doc("test line");
    Command* append_second_string = new AppendLineCommand("second_line", &text_doc);
    append_second_string->Execute();
    text_doc.Show();
    delete append_second_string;
}
