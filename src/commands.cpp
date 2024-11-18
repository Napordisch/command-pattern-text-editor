#include <string>
#include "commands.h"

AppendLineCommand::AppendLineCommand(const string& _appended_string, Receiver* _text) : appended_string(_appended_string), text(_text){}
void AppendLineCommand::Execute() {
    text->AppendLine(appended_string);
}

void AppendLineCommand::Undo() {
    text->DeleteLastLine();
}