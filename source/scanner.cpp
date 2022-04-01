#include <lib.hpp>
#include <scanner.hpp>

const std::unordered_map<std::string_view, lox::token_type> lox::scanner::keywords{
        {"and", lox::token_type::kw_and},
        {"class", lox::token_type::kw_class},
        {"else", lox::token_type::kw_else},
        {"false", lox::token_type::kw_false},
        {"for", lox::token_type::kw_for},
        {"fun", lox::token_type::kw_fun},
        {"if", lox::token_type::kw_if},
        {"nil", lox::token_type::kw_nil},
        {"or", lox::token_type::kw_or},
        {"print", lox::token_type::kw_print},
        {"return", lox::token_type::kw_return},
        {"super", lox::token_type::kw_super},
        {"this", lox::token_type::kw_this},
        {"true", lox::token_type::kw_true},
        {"var", lox::token_type::kw_var},
        {"while", lox::token_type::kw_while},
};

bool lox::scanner::is_at_end() const {
    return m_current >= m_source.size();
}

void lox::scanner::scan_token() {
    char c = advance();
    switch (c) {
        case '(':
            add_token(token_type::left_paren);
            break;
        case ')':
            add_token(token_type::right_paren);
            break;
        case '{':
            add_token(token_type::left_brace);
            break;
        case '}':
            add_token(token_type::right_brace);
            break;
        case ',':
            add_token(token_type::comma);
            break;
        case '.':
            add_token(token_type::dot);
            break;
        case '-':
            add_token(token_type::minus);
            break;
        case '+':
            add_token(token_type::plus);
            break;
        case ';':
            add_token(token_type::semicolon);
            break;
        case '*':
            add_token(token_type::star);
            break;
        case '!':
            if (match('=')) {
                add_token(token_type::bang_equal);
            } else {
                add_token(token_type::bang);
            }
            break;
        case '=':
            if (match('=')) {
                add_token(token_type::equal_equal);
            } else {
                add_token(token_type::equal);
            }
            break;
        case '<':
            if (match('=')) {
                add_token(token_type::less_equal);
            } else {
                add_token(token_type::less);
            }
            break;
        case '>':
            if (match('=')) {
                add_token(token_type::greater_equal);
            } else {
                add_token(token_type::greater);
            }
            break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !is_at_end()) {
                    advance();
                }
            } else {
                add_token(token_type::slash);
            }
        case ' ':
        case '\r':
        case '\t':
            // ignore whitespace
            break;
        case '\n':
            ++m_line;
            break;
        case '"':
            string();
            break;
        default:
            if (is_digit(c)) {
                number();
            } else if (is_alpha(c)) {
                identifier();
            } else {
                m_lib->error(m_line, "Unexpected character.");
            }
    }
}

char lox::scanner::advance() {
    char result = m_source[m_current];
    ++m_current;
    return result;
}

void lox::scanner::add_token(token_type type, object literal) {
    std::string text{&m_source[m_start], &m_source[m_current]};
    m_tokens.emplace_back(type, std::move(text), std::move(literal), m_line);
}

bool lox::scanner::match(char expected) {
    if (is_at_end()) {
        return false;
    }
    if (m_source[m_current] != expected) {
        return false;
    }

    ++m_current;
    return true;
}

char lox::scanner::peek() {
    if (is_at_end()) {
        return '\0';
    }
    return m_source[m_current];
}

char lox::scanner::peek_next() {
    if (static_cast<std::string_view::size_type>(m_current) + 1 >= m_source.size()) {
        return '\0';
    }

    return m_source[static_cast<std::string_view::size_type>(m_current) + 1];
}

void lox::scanner::string() {
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n') {
            ++m_line;
        }
        advance();
    }

    if (is_at_end()) {
        m_lib->error(m_line, "Unterminated string.");
        return;
    }

    // closing quote
    advance();

    auto value = std::string{
            &m_source[static_cast<std::string::size_type>(m_start) + 1], &m_source[m_current - 1]};
    add_token(token_type::string, std::move(value));
}

void lox::scanner::number() {
    while (is_digit(peek())) {
        advance();
    }

    if (peek() == '.' && is_digit(peek_next())) {
        // .
        advance();

        while (is_digit(peek())) {
            advance();
        }
    }

    auto value_str = std::string{&m_source[m_start], &m_source[m_current]};
    double value = std::strtod(value_str.c_str(), nullptr);
    add_token(token_type::number, value);
}

void lox::scanner::identifier() {
    while (is_alpha_numeric(peek())) {
        advance();
    }

    auto value = std::string_view{
            &m_source[m_start], static_cast<std::string_view::size_type>(m_current - m_start)};
    if (auto it = keywords.find(value); it != keywords.end()) {
        add_token(it->second);
    } else {
        add_token(token_type::identifier);
    }
}

bool lox::scanner::is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool lox::scanner::is_alpha(char c) {
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_';
}

bool lox::scanner::is_alpha_numeric(char c) {
    return is_alpha(c) || is_digit(c);
}

lox::scanner::scanner(library* lib, std::string_view source)
    : m_lib{lib}, m_source{source}, m_start{0}, m_current{0}, m_line{1} {}

std::vector<lox::token> lox::scanner::scan_tokens() {
    while (!is_at_end()) {
        m_start = m_current;
        scan_token();
    }

    m_tokens.emplace_back(token_type::eof, "", object{}, m_line);
    return m_tokens;
}
