#include <iostream>
#include <string>

class Command {
    public:
        virtual void Execute() = 0;
        virtual void Undo() = 0;
        virtual ~Command() {};
};

using std::string;
class Receiver {
    private:
        string content;

        void PrintLineNumber(unsigned int line_number) {
            using std::cout;
            if (line_number < 10) cout << ' ';
            cout << line_number <<'|'<< ' ';
        }

        unsigned int amount_of_lines;

        unsigned int CountLines() {
            if (content.empty()) return 0;
            
            unsigned int amount_of_newline_chars = 0;
            for (char i : content) {
                if (i == '\n') ++amount_of_newline_chars;
            }
            return amount_of_newline_chars + 1;
        }
    public:
        Receiver (const std::string& starting_line) : content(starting_line) {
            if (!content.empty()) amount_of_lines = CountLines();
        }
        void AppendLine(const string& appended_string) {
            content += "\n";
            content += appended_string;
            ++amount_of_lines;
        }
        void PrependLine(const string& prepended_string){
            ++amount_of_lines;
            content = prepended_string + "\n" + content;
        }
        void Show() {
            using std::cout;
            if (content.empty()) return;
            unsigned int current_line = 1;
            PrintLineNumber(current_line);
            for (char i : content) {
                cout << i;
                if (i == '\n') {
                    ++current_line;
                    PrintLineNumber(current_line);
                }
            }
            cout << '\n';
        }

        void DeleteLine(unsigned int line_number) {
            unsigned int current_line = 1;
            unsigned int current_character = 0;
            unsigned int line_start = 0;
            for (char i : content) {
                if (i == '\n') {
                    if (current_line == line_number) {
                        content.erase(line_start, current_character - line_start + 1);
                        --amount_of_lines;
                        break;
                    } else {
                        line_start = current_character + 1;
                        ++current_line;
                    }
                } else if (current_character == content.length() - 1 && current_line == line_number) {
                    content.erase(line_start, current_character - line_start + 1);
                    content.erase(content.length() - 1, 1);
                }
                ++current_character;
            }
        }

        void DeleteLastLine() {
            DeleteLine(amount_of_lines);

        }

        void InsertAfterLine(unsigned int line_number, std::string inserted_string) {
            unsigned int current_line = 1;
            unsigned int current_character = 0;
            unsigned int line_start = 0;
             for (char i : content) {
                if (i == '\n') {
                    if (current_line == line_number) {
                        if (current_character != content.length() - 1) {
                            inserted_string += '\n';
                        }
                        content.insert(current_character + 1, inserted_string);
                    }
                    ++current_line;
                }
                ++current_character;
            }
        }
};

class AppendLineCommand : public Command {
    
    private:
        Receiver* text;
        std::string appended_string;

    public:
        AppendLineCommand(const string& _appended_string, Receiver* _text) : appended_string(_appended_string), text(_text){}

        void Execute() override {
            text->AppendLine(appended_string);
        }

        void Undo() override {
            text->DeleteLastLine();
        }
};


int main() {
    Receiver text_doc("test line");
    Command* append_second_string = new AppendLineCommand("second_line", &text_doc);
    append_second_string->Execute();
    text_doc.Show();
    delete append_second_string;
}
