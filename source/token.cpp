#include <fmt/format.h>
#include <fmt/ostream.h>
#include <stdexcept>
#include <token.hpp>

std::ostream& operator<<(std::ostream& os, const lox::token& token) {
    fmt::print(os, "{}", token);
    return os;
}

lox::token::token(token_type type, std::string&& lexeme, object&& literal, int line)
    : type{type}, lexeme{std::move(lexeme)}, literal{std::move(literal)}, line{line} {}
