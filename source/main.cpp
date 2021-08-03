#include <iostream>
#include <string>

#include <lib.hpp>

#include <gsl/span>

int main(int argc, char* argv[])
{
  gsl::span args {argv, argc};
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
