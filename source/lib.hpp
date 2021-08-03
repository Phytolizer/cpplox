#pragma once

#include <string>
#include <string_view>

/**
 * @brief The core implementation of the executable
 *
 * This class makes up the library part of the executable, which means that the
 * main logic is implemented here. This kind of separation makes it easy to
 * test the implementation for the executable, because the logic is nicely
 * separated from the command-line logic implemented in the main function.
 */
struct library
{
  /**
   * @brief Simply initializes the name member to the name of the project
   */
  library();

  std::string name;
  bool had_error;

  int run_file(std::string_view filename);
  int run_prompt();
  void run(std::string_view source);

  void error(int line, std::string_view message);

private:
  void report(int line, std::string_view where, std::string_view message);
};
