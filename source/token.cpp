#include <stdexcept>

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <token.hpp>

std::ostream& operator<<(std::ostream& os, const lox::token& token)
{
  fmt::print(os, "{} {} ", token.type, token.lexeme);
  if (token.literal) {
    const lox::object::value_type* ptr = &*token.literal;

    // enumerate all possible types here
    if (const double* dptr = std::get_if<double>(ptr); dptr) {
      fmt::print(os, "{}", *dptr);
    } else {
      throw std::logic_error {"entered unreachable code"};
    }
  } else {
    fmt::print(os, "null");
  }
  return os;
}

lox::token::token(token_type type,
                  std::string&& lexeme,
                  object&& literal,
                  int line)
    : type {type}
    , lexeme {std::move(lexeme)}
    , literal {std::move(literal)}
    , line {line}
{
}
