#include "receiver.h"

#include <iostream>
#include <string>

using std::string;

void Receiver::PrintLineNumber(unsigned int line_number) const {
  using std::cout;
  if (line_number < 10) cout << ' ';
  cout << line_number << '|' << ' ';
}

unsigned int Receiver::CountLines() {
  if (content.empty()) return 0;

  unsigned int amount_of_newline_chars = 0;
  for (char i : content) {
    if (i == '\n') ++amount_of_newline_chars;
  }
  return amount_of_newline_chars + 1;
}

Receiver::Receiver(const std::string& starting_line) : content(starting_line) {
  if (!content.empty()) amount_of_lines = CountLines();
}

void Receiver::AppendLine(const string& appended_string) {
  content += "\n";
  content += appended_string;
  ++amount_of_lines;
}

void Receiver::PrependLine(const string& prepended_string) {
  ++amount_of_lines;
  content = prepended_string + "\n" + content;
}

void Receiver::Show() const {
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

std::string Receiver::DeleteLine(unsigned int line_number) {
  unsigned int current_line = 1;
  unsigned int current_character = 0;
  unsigned int line_start = 0;
  std::string deleted_line;
  for (char i : content) {
    if (i == '\n') {
      if (current_line == line_number) {
        deleted_line =
            content.substr(line_start, current_character - line_start);
        content.erase(line_start, current_character - line_start + 1);
        --amount_of_lines;
        break;
      } else {
        line_start = current_character + 1;
        ++current_line;
      }
    } else if (current_character == content.length() - 1 &&
               current_line == line_number) {
      deleted_line =
          content.substr(line_start, current_character - line_start + 1);
      content.erase(line_start, current_character - line_start + 1);
      content.erase(content.length() - 1, 1);
    }
    ++current_character;
  }
  return deleted_line;
}

std::string Receiver::DeleteLastLine() { return DeleteLine(amount_of_lines); }

void Receiver::InsertAfterLine(unsigned int line_number,
                               std::string inserted_string) {
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
std::string Receiver::GetContent() {
  return content;
}