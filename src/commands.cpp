#include "commands.h"

#include <string>

#include "receiver.h"

Command::Command(Receiver* _text) : text(_text) {}

AppendLineCommand::AppendLineCommand(const string& _appended_string,
                                     Receiver* _text)
    : appended_string(_appended_string), Command(_text) {}

void AppendLineCommand::Execute() { text->AppendLine(appended_string); }

void AppendLineCommand::Undo() { text->DeleteLastLine(); }

InsertLineCommand::InsertLineCommand(const string& _inserted_string,
                                     Receiver* _text, unsigned int _line)
    : inserted_string(_inserted_string), Command(_text), line(_line) {}

void InsertLineCommand::Execute() {
  text->InsertAfterLine(line, inserted_string);
}

void InsertLineCommand::Undo() { text->DeleteLine(line + 1); }