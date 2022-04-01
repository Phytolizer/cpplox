#pragma once

#include <cstddef>
#include <string_view>
#include <token.hpp>
#include <unordered_map>
#include <vector>

struct library;

namespace lox {
class scanner {
    library* m_lib;
    std::string_view m_source;
    std::vector<token> m_tokens;
    std::size_t m_start;
    std::size_t m_current;
    std::size_t m_line;

    static const std::unordered_map<std::string_view, token_type> keywords;

    [[nodiscard]] bool is_at_end() const;
    void scan_token();
    char advance();
    void add_token(token_type type, object literal = object{});
    [[nodiscard]] bool match(char expected);
    [[nodiscard]] char peek();
    [[nodiscard]] char peek_next();
    void string();
    void number();
    void identifier();
    [[nodiscard]] static bool is_digit(char c);
    [[nodiscard]] static bool is_alpha(char c);
    [[nodiscard]] static bool is_alpha_numeric(char c);

  public:
    explicit scanner(library* lib, std::string_view source);
    [[nodiscard]] std::vector<token> scan_tokens();
};
} // namespace lox
