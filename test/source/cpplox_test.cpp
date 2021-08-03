#include <lib.hpp>

auto main() -> int
{
  library lib;

  return lib.name == "cpplox" ? 0 : 1;
}
