#include <lib.hpp>

auto main() -> int
{
  library lib;

  lib.run("(){}");
  if (lib.had_error) {
    return 1;
  }

  return lib.name == "cpplox" ? 0 : 1;
}
