#include "commands.h"

#include <string>

Command::Command(Receiver* _text) : text(_text) {}

AppendLineCommand::AppendLineCommand(const string& _appended_string,
                                     Receiver* _text)
    : appended_string(_appended_string), Command(_text) {}

void AppendLineCommand::Execute() { text->AppendLine(appended_string); }

void AppendLineCommand::Undo() { text->DeleteLastLine(); }

InsertLineCommand::InsertLineCommand(const string& _inserted_string,
                                     Receiver* _text)
    : inserted_string(_inserted_string), Command(_text) {};
