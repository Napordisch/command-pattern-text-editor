#include "commands.h"

#include <string>

#include "receiver.h"

Command::Command(Receiver* _text) : text(_text) {}

AppendLineCommand::AppendLineCommand(const string& _appended_string,
                                     Receiver* _text)
    : appended_string(_appended_string), Command(_text) {}

AppendLineCommand::AppendLineCommand(Receiver* _text) : Command(_text) {}

void AppendLineCommand::SetAppendedString(const string& _appended_string) {
  appended_string = _appended_string;
}

void AppendLineCommand::Execute() { text->AppendLine(appended_string); }

void AppendLineCommand::Undo() { text->DeleteLastLine(); }

InsertLineCommand::InsertLineCommand(const string& _inserted_string,
                                     Receiver* _text, unsigned int _line)
    : inserted_string(_inserted_string), Command(_text), line(_line) {}

InsertLineCommand::InsertLineCommand(Receiver* _text) : Command(_text) {}

void InsertLineCommand::SetInsertedString(const string& _inserted_string) {
  inserted_string = _inserted_string;
}

void InsertLineCommand::SetLine(unsigned int _line) { line = _line; }

void InsertLineCommand::Execute() {
  text->InsertAfterLine(line, inserted_string);
}

void InsertLineCommand::Undo() { text->DeleteLine(line + 1); }

PrependLineCommand::PrependLineCommand(const string& _prepended_string,
                                       Receiver* _text)
    : prepended_string(_prepended_string), Command(_text) {}

PrependLineCommand::PrependLineCommand(Receiver* _text) : Command(_text) {}

void PrependLineCommand::SetPrependedString(
    const std::string& _prepended_string) {
  prepended_string = _prepended_string;
}

void PrependLineCommand::Execute() { text->PrependLine(prepended_string); }

void PrependLineCommand::Undo() { text->DeleteLine(1); }

DeleteLineCommand::DeleteLineCommand(unsigned int _line, Receiver* _text)
    : line(_line), Command(_text) {}

DeleteLineCommand::DeleteLineCommand(Receiver* _text) : Command(_text) {}

void DeleteLineCommand::SetLine(unsigned int _line) { line = _line; }

void DeleteLineCommand::Execute() { deleted_string = text->DeleteLine(line); }

void DeleteLineCommand::Undo() {
  text->InsertAfterLine(line - 1, deleted_string);
}

DeleteLastLineCommand::DeleteLastLineCommand(Receiver* _text)
    : Command(_text) {}

void DeleteLastLineCommand::Execute() {
  deleted_string = text->DeleteLastLine();
}

void DeleteLastLineCommand::Undo() { text->AppendLine(deleted_string); }