#include <gsl/span>
#include <iostream>
#include <lib.hpp>
#include <string>

int main(int argc, char* argv[]) {
    gsl::span args{argv, static_cast<gsl::span<char, gsl::dynamic_extent>::size_type>(argc)};
    library lib;
    if (args.size() > 2) {
        std::cout << "Usage: " << args[0] << " [script]\n";
        return 64;
    }
    if (args.size() == 2) {
        lib.run_file(args[1]);
    } else {
        lib.run_prompt();
    }
    return 0;
}
