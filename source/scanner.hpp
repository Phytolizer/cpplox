#pragma once

#include <string_view>
#include <vector>

#include <token.hpp>

struct library;

namespace lox
{
class scanner
{
  library *m_lib;
  std::string_view m_source;
  std::vector<token> m_tokens;
  int m_start;
  int m_current;
  int m_line;

  [[nodiscard]] bool is_at_end() const;
  void scan_token();
  [[nodiscard]] char advance();
  void add_token(token_type type, object literal = object {});

public:
  explicit scanner(library *lib, std::string_view source);
  [[nodiscard]] std::vector<token> scan_tokens();
};
}  // namespace lox
