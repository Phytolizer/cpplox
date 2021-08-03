#include <lib.hpp>
#include <scanner.hpp>

bool lox::scanner::is_at_end() const
{
  return m_current >= m_source.size();
}

void lox::scanner::scan_token()
{
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
    default:
      m_lib->error(m_line, "Unexpected character.");
  }
}

char lox::scanner::advance()
{
  char result = m_source[m_current];
  ++m_current;
  return result;
}

void lox::scanner::add_token(token_type type, object literal)
{
  std::string text {&m_source[m_start], &m_source[m_current]};
  m_tokens.emplace_back(type, std::move(text), std::move(literal), m_line);
}

lox::scanner::scanner(library* lib, std::string_view source)
    : m_lib {lib}
    , m_source {source}
    , m_start {0}
    , m_current {0}
    , m_line {1}
{
}

std::vector<lox::token> lox::scanner::scan_tokens()
{
  while (!is_at_end()) {
    m_start = m_current;
    scan_token();
  }

  m_tokens.emplace_back(token_type::eof, "", object {}, m_line);
  return m_tokens;
}
