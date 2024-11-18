#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include "receiver.h"
using std::string;

class Command {
    public:
        virtual void Execute() = 0;
        virtual void Undo() = 0;
        virtual ~Command() {};
};

class AppendLineCommand : public Command {
    
    private:
        Receiver* text;
        std::string appended_string;

    public:
        AppendLineCommand(const string& _appended_string, Receiver* _text);

        void Execute() override;

        void Undo() override;
};

#endif