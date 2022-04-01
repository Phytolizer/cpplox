#include <algorithm>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fstream>
#include <iostream>
#include <lib.hpp>
#include <scanner.hpp>

library::library() : name{"cpplox"}, had_error{false} {}

int library::run_file(std::string_view filename) {
    std::ifstream file{std::string{filename}};
    std::string line;
    std::string bytes;
    while (std::getline(file, line)) {
        std::copy(line.begin(), line.end(), std::back_inserter(bytes));
        // std::getline doesn't include the newline
        bytes.push_back('\n');
    }
    run(bytes);

    if (had_error) {
        return 65;
    }
    return 0;
}

int library::run_prompt() {
    while (true) {
        fmt::print("> ");
        std::string line;
        if (!std::getline(std::cin, line)) {
            fmt::print("\n");
            break;
        }
        run(line);
    }

    return 0;
}

void library::run(std::string_view source) {
    auto scanner = lox::scanner{this, source};
    auto tokens = scanner.scan_tokens();

    // for now, just print the tokens
    for (const auto& token : tokens) {
        fmt::print("{}\n", token);
    }
}

void library::error(int line, std::string_view message) {
    report(line, "", message);
}

void library::report(int line, std::string_view where, std::string_view message) {
    fmt::print(std::cerr, "[line {}] Error{}: {}\n", line, where, message);
    had_error = true;
}
