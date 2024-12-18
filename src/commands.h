#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

#include "receiver.h"
using std::string;

class Command {
 protected:
  Receiver *text;

 public:
  Command(Receiver *_text);
  virtual void Execute() = 0;
  virtual void Undo() = 0;
  virtual ~Command() {};
};

class AppendLineCommand : public Command {
 private:
  std::string appended_string;

 public:
  AppendLineCommand(Receiver *_text);

  AppendLineCommand(const string &_appended_string, Receiver *_text);

  void SetAppendedString(const string &_appended_string);

  void Execute() override;

  void Undo() override;
};

class InsertLineCommand : public Command {
 private:
  std::string inserted_string;
  unsigned int line;  // after which to insert

 public:
  InsertLineCommand(const string &_inserted_string, Receiver *_text,
                    unsigned int _line);

  InsertLineCommand(Receiver *_text);

  void SetInsertedString(const string &_inserted_string);

  void SetLine(unsigned int _line);

  void Execute() override;
  void Undo() override;
};

class PrependLineCommand : public Command {
 private:
  std::string prepended_string;

 public:
  PrependLineCommand(const string &_prepended_string, Receiver *_text);
  PrependLineCommand(Receiver *_text);
  void SetPrependedString(const std::string& _prepended_string);

  void Execute() override;

  void Undo() override;
};

class DeleteLineCommand : public Command {
 private:
  unsigned int line;
  std::string deleted_string;

 public:
  DeleteLineCommand(unsigned int _line, Receiver *_text);
  DeleteLineCommand(Receiver *_text);
  void SetLine(unsigned int _line);

  void Execute() override;
  void Undo() override;
};

class DeleteLastLineCommand : public Command {
 private:
  std::string deleted_string;

 public:
  DeleteLastLineCommand(Receiver *_text);
  void Execute() override;
  void Undo() override;
};

#endif