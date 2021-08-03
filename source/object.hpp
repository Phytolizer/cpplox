#pragma once

#include <optional>
#include <variant>

namespace lox
{
using object = std::optional<std::variant<double>>;
}  // namespace lox
