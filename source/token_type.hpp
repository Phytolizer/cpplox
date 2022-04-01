#pragma once

#include <fmt/core.h>
#include <magic_enum.hpp>

namespace lox {
enum class token_type
{
    left_paren,
    right_paren,
    left_brace,
    right_brace,
    comma,
    dot,
    minus,
    plus,
    semicolon,
    slash,
    star,
    bang,
    bang_equal,
    equal,
    equal_equal,
    greater,
    greater_equal,
    less,
    less_equal,
    identifier,
    string,
    number,

    kw_and,
    kw_class,
    kw_else,
    kw_false,
    kw_for,
    kw_fun,
    kw_if,
    kw_nil,
    kw_or,
    kw_print,
    kw_return,
    kw_super,
    kw_this,
    kw_true,
    kw_var,
    kw_while,

    eof
};
} // namespace lox

template <> struct fmt::formatter<lox::token_type> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const lox::token_type& type, FormatContext& ctx) -> decltype(ctx.out()) {
        return format_to(ctx.out(), "{}", magic_enum::enum_name(type));
    }
};
