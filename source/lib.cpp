#include <algorithm>
#include <fstream>
#include <iostream>

#include <lib.hpp>
#include <scanner.hpp>

library::library()
    : name("cpplox")
{
}

void library::run_file(std::string_view filename)
{
  std::ifstream file {std::string {filename}};
  std::string line;
  std::string bytes;
  while (std::getline(file, line)) {
    std::copy(line.begin(), line.end(), std::back_inserter(bytes));
    // std::getline doesn't include the newline
    bytes.push_back('\n');
  }
  run(bytes);
}

void library::run_prompt()
{
  while (true) {
    std::cout << "> " << std::flush;
    std::string line;
    if (!std::getline(std::cin, line)) {
      break;
    }
    run(line);
  }
}

void library::run(std::string_view source)
{
  auto scanner = lox::scanner {source};
  auto tokens = scanner.scan_tokens();

  // for now, just print the tokens
  for (const auto& token : tokens) {
    std::cout << token << "\n";
  }
}
