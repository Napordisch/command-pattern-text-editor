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
  AppendLineCommand(const string &_appended_string, Receiver *_text);

  void Execute() override;

  void Undo() override;
};

class InsertLineCommand : public Command {
 private:
  std::string inserted_string;

 public:
  InsertLineCommand(const string &_inserted_string, Receiver *_text);

  void Execute() override;
  void Undo() override;
};

#endif