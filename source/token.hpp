#pragma once

#include <ostream>
#include <stdexcept>
#include <string>

#include <fmt/core.h>
#include <fmt/format.h>
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

template<>
struct fmt::formatter<lox::token>
{
  // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
  constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
  {
    const auto* it = ctx.begin();
    if (it != ctx.end() && *it != '}') {
      throw format_error {"invalid format"};
    }
    return it;
  }

  template<typename FormatContext>
  auto format(const lox::token& token, FormatContext& ctx)
      -> decltype(ctx.out())
  {
    auto out = format_to(ctx.out(), "{} {} ", token.type, token.lexeme);
    if (token.literal) {
      const lox::object::value_type* ptr = &*token.literal;
      if (const double* dp = std::get_if<double>(ptr); dp) {
        return format_to(out, "{}", *dp);
      }
      throw std::logic_error {"invalid token"};
    }
    return format_to(out, "null");
  }
};
