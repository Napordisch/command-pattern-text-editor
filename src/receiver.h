#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <string>

using std::string;
class Receiver {
 private:
  string content;

  void PrintLineNumber(unsigned int line_number) const;

  unsigned int amount_of_lines;

  unsigned int CountLines();

 public:
  Receiver(const std::string& starting_line);
  void AppendLine(const string& appended_string);
  void PrependLine(const string& prepended_string);
  void Show() const;

  void DeleteLine(unsigned int line_number);

  void DeleteLastLine();

  void InsertAfterLine(unsigned int line_number, std::string inserted_string);
};
#endif