#pragma once

#include <optional>
#include <variant>
#include <string>

namespace lox
{
using object = std::optional<std::variant<double, std::string>>;
}  // namespace lox
