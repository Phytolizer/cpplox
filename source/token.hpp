#pragma once

#include <ostream>
#include <string>

#include <object.hpp>
#include <token_type.hpp>

namespace lox
{
struct token
{
  token_type type;
  std::string lexeme;
  object literal;
  int line;

  token(token_type type, std::string&& lexeme, object&& literal, int line);
};
}  // namespace lox

std::ostream& operator<<(std::ostream& os, const lox::token& token);
