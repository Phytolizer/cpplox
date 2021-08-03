#pragma once

#include <string_view>
#include <vector>

#include <token.hpp>

namespace lox
{
class scanner
{
public:
  explicit scanner(std::string_view source);
  std::vector<token> scan_tokens();
};
}  // namespace lox
