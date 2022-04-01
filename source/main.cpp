#include <cstddef>
#include <fmt/core.h>
#include <gsl/span>
#include <lib.hpp>
#include <string>

int main(int argc, char* argv[]) {
    std::span args{argv, static_cast<std::size_t>(argc)};
    library lib;
    if (args.size() > 2) {
        fmt::print("Usage: {} [script]\n", args[0]);
        return 64;
    }
    if (args.size() == 2) {
        return lib.run_file(args[1]);
    } else {
        return lib.run_prompt();
    }
}
