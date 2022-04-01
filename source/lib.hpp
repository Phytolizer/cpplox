#pragma once

#include <string>
#include <string_view>

struct library {
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
