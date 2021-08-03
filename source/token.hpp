#pragma once

#include <ostream>

namespace lox
{
struct token
{
};
}  // namespace lox

std::ostream& operator<<(std::ostream& os, const lox::token& token);
