#pragma once

#include <fmt/core.h>
#include <fmt/format.h>
#include <object.hpp>
#include <ostream>
#include <stdexcept>
#include <string>
#include <token_type.hpp>

namespace lox {
struct token {
    token_type type;
    std::string lexeme;
    object literal;
    int line;

    token(token_type type, std::string&& lexeme, object&& literal, int line);
};
} // namespace lox

std::ostream& operator<<(std::ostream& os, const lox::token& token);

template <> struct fmt::formatter<lox::token> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const lox::token& token, FormatContext& ctx) -> decltype(ctx.out()) {
        auto out = format_to(ctx.out(), "{} '{}' ", token.type, token.lexeme);
        if (token.literal) {
            switch (token.literal->index()) {
                case lox::object_kind::number:
                    return format_to(out, "{}", std::get<lox::object_kind::number>(*token.literal));
                case lox::object_kind::string:
                    return format_to(out, "{}", std::get<lox::object_kind::string>(*token.literal));
            }
            throw std::logic_error{"invalid token"};
        }
        return format_to(out, "null");
    }
};
