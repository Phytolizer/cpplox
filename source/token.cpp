#include <fmt/format.h>
#include <fmt/ostream.h>
#include <stdexcept>
#include <token.hpp>

std::ostream& operator<<(std::ostream& os, const lox::token& token) {
    fmt::print(os, "{} {} ", token.type, token.lexeme);
    if (token.literal) {
        const lox::object::value_type* ptr = &*token.literal;

        // enumerate all possible types here
        if (const double* dptr = std::get_if<double>(ptr); dptr) {
            fmt::print(os, "{}", *dptr);
        } else if (const std::string* sptr = std::get_if<std::string>(ptr); sptr) {
            fmt::print(os, "{}", *sptr);
        } else {
            throw std::logic_error{"entered unreachable code"};
        }
    } else {
        fmt::print(os, "null");
    }
    return os;
}

lox::token::token(token_type type, std::string&& lexeme, object&& literal, int line)
    : type{type}, lexeme{std::move(lexeme)}, literal{std::move(literal)}, line{line} {}
